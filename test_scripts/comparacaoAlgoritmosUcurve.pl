#!/usr/bin/perl -w

# comparacaoAlgoritmosUcurve.pl -- Programinha que compara o UCS contra outros algoritmos
#                                  (U-Curve original, SFS, SFFS, Busca exaustiva)
# 
# Versão original: M.S.Reis, Ago.21.2010
#
# SINTAXE: ./comparacaoAlgoritmosUcurve.pl <num_testes> <tam_testes> <prefixo_dos_nomes_dos_arquivos_de_saida> <w_operador?> <modo_heuristico?> [limite de tempo]
#
# num_testes: numero de repeticoes de um teste com uma mesma instancia
#
# tam_testes: tamanho maximo dos conjuntos S nos testes
#
# w_operador?: 0 se sao dados simulados (ABS_SUM), 1 se e' W-operador
#
# modo_heuristico?: 0 se UCS e B&B buscam a solucao exata, 
#                   1 se trabalham no modo heuristico 1 (com pré-processamento que define um threshold de numero de nos),
#                   2 se trabalham no modo heuristico 2 (com limite de tempo)
#
#
# Testa para ABS_SUM 
#
# Update: 22-set-2010: agora tambem inclui busca exaustiva (es)
#         21-jun-2011: adicionado Branch and Bound
#         15-abr-2012: adicionado o modo heuristico
#         16-ago-2012: refatoracao que especifica os solvers a partir de uma lista
#         04-mai-2013: modo heuristico com limite de tempo

use POSIX;  # ceil () and floor ()
use strict;
use Time::HiRes qw (gettimeofday tv_interval);

my $n;

# list of solvers; SFFS is required for the heuristic mode 
#

my @solvers = (#"UCSO", "UCSRT",
                "UCSR7",
                 "UCSR6", "UCSR5", 
                 # "UCSR4", "UCS", 
                 "UBB", "ES");

my $number_of_solvers = @solvers;

my $is_W_operator = 0;      # 0: ABS_SUM e cria instancias aleatorias usando o programa "create_featsel_instance.pl" 
                            # 1: Mean Conditional Entropy, pegando arquivos .DAT do diretorio ./input


my $is_heuristic_mode = 0;  # 0: optimal search mode, 1: heuristic mode 1, 2: heuristic mode 2

my $TIME_LIMIT = 2000000;    # time limit for the heuristic mode 2 (in microseconds)

my $funcao = "mce";
my $window_size = " -n 3 "; # window size (number of elements of the set S)

my $repeticoes = 10;  # numero de repeticoes de cada teste
my $MAX = 100000;     # valor maximo dos elementos de S
my $saida = "arquivo.html";


if ( (@ARGV == 5) || (@ARGV == 6) )
{
  $repeticoes = $ARGV[0];
  $n = $ARGV[1];
  $saida = $ARGV[2];
  $is_W_operator = $ARGV[3];
  $is_heuristic_mode = $ARGV[4];
  (@ARGV == 6) and $TIME_LIMIT = $ARGV[5];
}
else
{
  die "\nSintaxe: ./comparacaoAlgoritmosUCurve.pl <num_testes> <tam_testes> <prefixo_dos_nomes_dos_arquivos_de_saida> <w_operador?> <modo_heuristico?> [limite de tempo]\n\n";
}

if (! $is_W_operator)
  {
    $funcao = "abs_sum";
    $window_size = "";
  }

open (OUT, ">output/table_$saida.html") or die "Erro ao abrir arquivo HTML de saida!\n";
open (OUT2, ">output/table_$saida.tex") or die "Erro ao abrir arquivo TEX de saida!\n";
open (OUT3, ">output/table_$saida.ucs.txt") or die "Erro ao abrir arquivo TXT de saida!\n";

if ($is_heuristic_mode == 1)
  {
    open (OUT4, ">output/table_" . $saida . "_heuristic.tex") or die "Erro ao abrir arquivo TEX de saida!\n";
  }

if ($is_W_operator)
  {
    open (OUT5, ">output/table_" . $saida . "_W_operator.txt") or die "Erro ao abrir arquivo TXT de saida!\n";
  }

open (OUT6, ">output/table_$saida.pfs.txt") or die "Erro ao abrir arquivo TXT de saida!\n";

if ($is_heuristic_mode == 2)
  {
    open (OUT7, ">output/table_" . $saida . "_time_limit.txt") or die "Erro ao abrir arquivo TEX de saida!\n";
  }


# comparacao com 2 colunas iniciais, + 2 colunas para cada solver

# imprimindo o cabecalho da tabela LaTeX
#
print OUT2 "\\begin{table}[!t] \\begin{center} \\begin{tabular}{\@{}ccccc";
print OUT2 "c" foreach (1..(3 * $number_of_solvers));
print OUT2 "\@{}} \\toprule" . "\n";
printf OUT2 "\\multicolumn{2}{c}{Size of instance} & \\phantom{abc} & \\multicolumn{%d}{c}{Time (sec)} & \\phantom{abc} & \\multicolumn{%d}{c}{\\\# Computed nodes} & \\phantom{abc} & \\multicolumn{%d}{c}{\\\# The best solution}\\\\" . "\n", $number_of_solvers, $number_of_solvers, $number_of_solvers;
print OUT2 "\\cline{1-2}";
for (my $i = 0; $i < 3; $i++)
  {
    printf OUT2 "\\cline{%d-%d} ", ($i * ($number_of_solvers + 1) ) + 4, ($i * ($number_of_solvers + 1) ) + 3 + $number_of_solvers;
  }
print OUT2 "\n";

print OUT2 "\$|S|\$ & \$2^{|S|}\$  && ";
for (my $i = 0; $i < $number_of_solvers; $i++)
  {
    printf OUT2 " \$\\proc{%s}\$ &", $solvers[$i];
  }
print OUT2 "&";
for (my $i = 0; $i < $number_of_solvers; $i++)
  {
    printf OUT2 " \$\\proc{%s}\$ &", $solvers[$i];
  }
print OUT2 "&";
for (my $i = 0; $i < $number_of_solvers; $i++)
  {
    printf OUT2 " \$\\proc{%s}\$ &", $solvers[$i];
  }
print OUT2 "\\\\ \\hline" . "\n";


# imprimindo a tabela HTML
#
print OUT "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\n";
print OUT "<HTML><HEAD>
<meta http-equiv=\"content-type\" content=\"text/html; charset=iso-8859-1\">
<TITLE>Feature selection algorithms comparison</TITLE></HEAD>\n";

print OUT "<BODY><H1>Feature selection algorithms comparison</H1><HR>\n";
print OUT "<H3>Table description:</H3>\n";
print OUT "<EM>2^|S|:</EM> size of the search space of an instance of S elements<BR>\n";
print OUT "<EM>Total Time (sec)</EM> required time to run the XXX algorithm (average of $repeticoes runnings)<BR>\n";
print OUT "<EM>Cost Function Time (sec)</EM> required time for the computation of all calls the cost function, during the running of the XXX algorithm (average of $repeticoes runnings)<BR>\n";
print OUT "<EM>\# Computed nodes:</EM> number of times the cost of a subset is computed by XXX algorithm (average of $repeticoes runnings)<BR>\n";
# print OUT "<EM>\# Suboptimal results:</EM> number of times (out of $repeticoes) that XXX algorithm had a suboptimal solution<BR><HR><BR>\n";
print OUT "<EM>\# The best solution:</EM> number of times (out of $repeticoes) that XXX algorithm had the best solution among all the solvers<BR><HR><BR>\n";

print OUT "<TABLE border='5'>\n";
print OUT "<TR bgcolor='yellow'>\n";
print OUT "<TD colspan=2><CENTER>Size of instance</CENTER></TD>\n";

my $col_span = $number_of_solvers;

print OUT "<TD><CENTER>&nbsp;</CENTER></TD>
       <TD colspan=$col_span><CENTER>Total Time (sec)</CENTER></TD>
       <TD><CENTER>&nbsp;</CENTER></TD>
       <TD colspan=$col_span><CENTER>Cost Function Time (sec)</CENTER></TD>
       <TD><CENTER>&nbsp;</CENTER></TD>
       <TD colspan=4><CENTER>Average time updating restrictions (sec)</CENTER></TD>
       <TD><CENTER>&nbsp;</CENTER></TD>
       <TD colspan=4><CENTER>Average time reducing restrictions (sec)</CENTER></TD>
       <TD><CENTER>&nbsp;</CENTER></TD>
       <TD colspan=2><CENTER>Average restriction reduction</CENTER></TD>
       <TD><CENTER>&nbsp;</CENTER></TD>
       <TD colspan=4><CENTER>Average time consulting restrictions (sec)</CENTER></TD>
       <TD><CENTER>&nbsp;</CENTER></TD>
       <TD colspan=4><CENTER>\# Restrictions updates</CENTER></TD>
       <TD><CENTER>&nbsp;</CENTER></TD>
       <TD colspan=4><CENTER>\# Restrictions consults</CENTER></TD>
       <TD><CENTER>&nbsp;</CENTER></TD>
       <TD colspan=$col_span><CENTER>\# Computed nodes</CENTER></TD>
       <TD><CENTER>&nbsp;</CENTER></TD>
       <TD colspan=$col_span><CENTER>\# The best solution</CENTER></TD>

       </TR>\n";
print OUT "<TR bgcolor='yellow'>\n";

# Size of instance
print OUT "<TD><CENTER>&nbsp;|S|&nbsp;</CENTER></TD><TD><CENTER>&nbsp;2^|S|&nbsp;</CENTER></TD>";

# Total Time
print OUT  "<TD><CENTER>&nbsp;</CENTER></TD>";
for (my $i = 0; $i < $number_of_solvers; $i++)
  {
    printf OUT "<TD><CENTER>&nbsp; %s &nbsp;</CENTER></TD>", $solvers[$i];
  }

# Cost Function Time
print OUT  "<TD><CENTER>&nbsp;</CENTER></TD>";
for (my $i = 0; $i < $number_of_solvers; $i++)
  {
    printf OUT "<TD><CENTER>&nbsp; %s &nbsp;</CENTER></TD>", $solvers[$i];
  }

#entrei
# Time updating restrictions
print OUT  "<TD><CENTER>&nbsp;</CENTER></TD>";
for (my $i = 0; $i < 4; $i++)
  {
    printf OUT "<TD><CENTER>&nbsp; %s &nbsp;</CENTER></TD>", $solvers[$i];
  }

# Time reducing restrictions
print OUT  "<TD><CENTER>&nbsp;</CENTER></TD>";
for (my $i = 0; $i < 4; $i++)
  {
    printf OUT "<TD><CENTER>&nbsp; %s &nbsp;</CENTER></TD>", $solvers[$i];
  }

# Restriction reduction
print OUT  "<TD><CENTER>&nbsp;</CENTER></TD>";
print OUT "<TD><CENTER>&nbsp; 1&nbsp;Red.   &nbsp;</CENTER></TD>";
print OUT "<TD><CENTER>&nbsp; 100&nbsp;Red. &nbsp;</CENTER></TD>";

# Time consulting
print OUT  "<TD><CENTER>&nbsp;</CENTER></TD>";
for (my $i = 0; $i < 4; $i++)
  {
    printf OUT "<TD><CENTER>&nbsp; %s &nbsp;</CENTER></TD>", $solvers[$i];
  }

# # of restriction Updates
print OUT  "<TD><CENTER>&nbsp;</CENTER></TD>";
for (my $i = 0; $i < 4; $i++)
  {
    printf OUT "<TD><CENTER>&nbsp; %s &nbsp;</CENTER></TD>", $solvers[$i];
  }

# # of restriction consults
print OUT  "<TD><CENTER>&nbsp;</CENTER></TD>";
for (my $i = 0; $i < 4; $i++)
  {
    printf OUT "<TD><CENTER>&nbsp; %s &nbsp;</CENTER></TD>", $solvers[$i];
  }
#sai

# # of computed nodes
print OUT  "<TD><CENTER>&nbsp;</CENTER></TD>";
for (my $i = 0; $i < $number_of_solvers; $i++)
  {
    printf OUT "<TD><CENTER>&nbsp; %s &nbsp;</CENTER></TD>", $solvers[$i];
  }

# # of best solutions found
print OUT  "<TD><CENTER>&nbsp;</CENTER></TD>";
for (my $i = 0; $i < $number_of_solvers; $i++)
  {
    printf OUT "<TD><CENTER>&nbsp; %s &nbsp;</CENTER></TD>", $solvers[$i];
  }
printf OUT "</TR>\n";



print OUT3 "\n= = = = UCS{2a, 2b} additional data, average of $repeticoes runnings = = = =\n\n";
printf OUT3 "Solver    2^|S|     Time (s)     # Nodes     # Max graph size     # Calls of DFS     # Calls of Minimal (Maximal)\n";


print OUT6 "\n= = = = PFS additional data, average of $repeticoes runnings = = = =\n\n";
printf OUT6 "2^|S|     Time (s)     # Nodes     # Max forest A size     # Max forest B size     # Iterations\n";


if ($is_W_operator)
  {
    print OUT5 "\n= = = = Solvers additional data, best solution for each W-operator = = = =\n\n";
    printf OUT5 "# Test (file)";
    for (my $i = 0; $i < $number_of_solvers; $i++)
      {
	printf OUT5 "   %s    ", $solvers[$i];
      }
    printf OUT5 "\n";
  }


if ($is_heuristic_mode == 1)
  {
    print OUT4 "\\begin{table}[!t] \\begin{center} \\begin{tabular}{\@{}ccccc";
    print OUT4 "c" foreach (1..$number_of_solvers);
    print OUT4 "\@{}} \\toprule" . "\n";
    print OUT4 "\\multicolumn{2}{c}{Size of instance} & \\phantom{abc} & \\multicolumn{$number_of_solvers}{c}{\\\# Computed nodes} & \\phantom{abc} & Threshold\\\\" . "\n";
    print OUT4 "\\cline{1-2}";
    for (my $i = 0; $i < 2; $i++)
      {
	printf OUT4 "\\cline{%d-%d} ", ($i * $number_of_solvers) + 4, ($i * $number_of_solvers) + 3 + $number_of_solvers;
      }
    print OUT4 "\n";
    print OUT4 "\$|S|\$ & \$2^{|S|}\$  && ";
    for (my $i = 0; $i < $number_of_solvers; $i++)
      {
	printf OUT4 " \$\\proc{%s}\$ &", $solvers[$i];
      }
    print OUT4 "&";
    print OUT4 "\\\\ \\hline" . "\n";
  }

my %tempo_total;
my %tempo_funcao_custo;
my $max_time = 0;

my @experiments;
if ($is_W_operator)
  {
#    @experiments = (3, 5, 9, 13, 17, 21, 25, 33); # each experiment i has a W-operator window with i points
    @experiments = (1, 2, 3, 4, 5, 6, 7, 8, 12, 13, 14, 15, 16, 17); # each experiment i has a W-operator window with i points

  }
else  
  {
    @experiments = (1..$n);  # each simulated data experiment i has as search space a Boolean lattice of degree i
  }

foreach my $i (@experiments)    
{

  print "Starting iteration $i... ";

  # this informaton is extracted from all solvers
  #
  my @average_calls_of_cost_function;
  my @average_time_of_cost_function;
  my @average_time_of_solver;
  my @number_of_times_that_has_a_best_solution;



  for (my $k = 0; $k < $number_of_solvers; $k++)
    { 
      $average_calls_of_cost_function[$k] = 0;
      $number_of_times_that_has_a_best_solution[$k] = 0;
    }

  my $argument_t2 = " ";

  my @arquivo;   # diretorio que armazena as instancias de cada linha das tabelas

  if (! $is_W_operator)
    {
      # cria $repeticoes arquivos .XML para os testes com dados simulados
      #
      foreach (1..$repeticoes)
	{
	  system ("./createFeatselInstance.pl $i $MAX > input/teste$_.xml");
	}
      
      # carrega os arquivos .XML para dados simulados
      #
      opendir(my $dh, "input") || die "can't opendir input: $!";
      @arquivo = grep { /.*\.xml$/ && -f "input/$_" } readdir($dh);
      closedir $dh;
    }
  else
    {
      # carrega os arquivos .DAT das amostras de pares de imagens
      #
      opendir(my $dh, "input/$i") || die "can't opendir input: $!";
      @arquivo = grep { /.*\.dat$/ && -f "input/$i/$_" } readdir($dh);
      closedir $dh;
      if ($#arquivo < ($n-1))
	{
	  $n = $#arquivo;
	}
      
      # provides the subdirectory of the samples of the current window size $i
      $arquivo[$_] = "$i/" . $arquivo[$_] foreach 0..$#arquivo;

      $window_size = " -n 16 ";    # current window size (use $i to dynamical size change)

      $repeticoes = $#arquivo + 1;
    }

  ##############################################################################################
  ##############################################################################################
  
  ## GERA A TABELA DO MODO HEURISTICO (SE APLICAVEL)
  
  ##############################################################################################

  if ($is_heuristic_mode == 1)
   {

     # este parametro eh utilizado na segunda etapa
     # de uma busca exaustiva!
     #
     my $NUMERO_MAXIMO_DE_CHAMADAS_DA_FUNCAO_CUSTO = 0;

     foreach (1..$repeticoes)
       {

	 my $best_solution;
	 my @minimum_of_solvers;
	 my $j = $_;   # LEMBRETE: a lista de arquivos comeca pelo indice zero!

	 # print "\nTeste com SFFS\n";
	 system ("./bin/featsel $window_size -a sffs -c $funcao -f input/" . $arquivo[$j-1] . " > result.log");
	 open (ARQ, "result.log");
	 while (<ARQ>)
	   {
	     if ($_ =~ /\<\d+\>\s+\:\s+(\S+)/)
	       {
		 $best_solution = $1;
	       }
	   }
	 close (ARQ);
	 # 
	 # fim da iteracao com SFFS
	 
	 my $argument_t1 = " -t1 " . $best_solution . " ";
	 	 
	 for (my $k = 0; $k < $number_of_solvers; $k++)
	   {
	     my $current_solver = lc $solvers[$k];
	     # print "\nTeste com %s\n", $solvers[$k];
	     system ("./bin/featsel $window_size -a " . $current_solver . " -c $funcao -f input/" . $arquivo[$j-1]  . $argument_t1 . " > result.log");
	     open (ARQ, "result.log");
	     while (<ARQ>)
	       {
		 if ($_ =~ /\<\d+\>\s+\:\s+(\S+)/)
		   {
		     $minimum_of_solvers[$k] = $1;
		   }
		 elsif ($_ =~ /^Number\s+of\s+visited\s+subsets\:\s+(\S+)/)
		   {
		     $average_calls_of_cost_function[$k] += $1;
		   }
	       }
	     close (ARQ);
	 
	     if ($best_solution > $minimum_of_solvers[$k])
	       {
		 $best_solution = $minimum_of_solvers[$k];
	       }
               else {
                   exit;
               }
	   }
	 
	 for (my $k = 0; $k < $number_of_solvers; $k++)
	   {
	     if ($minimum_of_solvers[$k] == $best_solution)
	       {
		  $number_of_times_that_has_a_best_solution[$k]++;
	       }
	   }
	 
       } # foreach(1..$repeticoes)

     
     for (my $k = 0; $k < $number_of_solvers; $k++)
       {
	 $average_calls_of_cost_function[$k] /= $repeticoes;	 
	 if ($NUMERO_MAXIMO_DE_CHAMADAS_DA_FUNCAO_CUSTO < $average_calls_of_cost_function[$k])
	   {
	     $NUMERO_MAXIMO_DE_CHAMADAS_DA_FUNCAO_CUSTO = ceil ($average_calls_of_cost_function[$k]);
	   }
       }	     
     
     $argument_t2 = " -t2 " . $NUMERO_MAXIMO_DE_CHAMADAS_DA_FUNCAO_CUSTO . " "; 
     # print " (argument t2 is: " . $argument_t2 . ") ";
     
     # imprime a tabela do pre-processamento
     #
     printf OUT4 "%2d & ", $i;
     printf OUT4 "%7d ", 2 ** $i;
     printf OUT4 "&";
     for (my $k = 0; $k < $number_of_solvers; $k++)
      {
	printf OUT4 "& %5.2f ", $average_calls_of_cost_function[$k];
      }
     printf OUT4 "&";
     printf OUT4 "& " . $NUMERO_MAXIMO_DE_CHAMADAS_DA_FUNCAO_CUSTO . "\\\\ \n";
     
   } # is_heuristic_mode


  ##############################################################################################
  ##############################################################################################

  ### GERA A TABELA NORMAL
  
  ##############################################################################################

  # UCS, UCS2a, and UCS2b algorithms only
  #
  my @average_restriction_update_time;
  my @average_restriction_consult_time;
  my @average_restriction_reduce_time;
  my @average_restriction_update;
  my @average_restriction_consult;
  my @average_calls_DFS;                
  my @average_graph_size;
  my @average_calls_minimal_maximal;  # equivalent to the average number of iterations of the main algorithm
  
  my $restriction_max0;
  my $average_restriction_red1;
  my $average_restriction_red100;

  # PFS algorithm only
  #
  my @average_forest_A_size;
  my @average_forest_B_size;
  my @average_number_of_iterations;

  for (my $k = 0; $k < $number_of_solvers; $k++)
    {
      $average_restriction_update_time[$k] = 0;
      $average_restriction_consult_time[$k] = 0;
      $average_restriction_reduce_time[$k] = 0;
      $average_restriction_update[$k] = 0;
      $average_restriction_consult[$k] = 0;

      $restriction_max0 = 0;
      $average_restriction_red1 = 0;
      $average_restriction_red100 = 0;

      $average_calls_of_cost_function[$k] = 0;
      $average_time_of_cost_function[$k] = 0;
      $average_time_of_solver[$k] = 0;
      $number_of_times_that_has_a_best_solution[$k] = 0;

      $average_calls_DFS[$k] = 0;                
      $average_graph_size[$k] = 0;
      $average_calls_minimal_maximal[$k] = 0; 
      $average_forest_A_size[$k] = 0;
      $average_forest_B_size[$k] = 0;
      $average_number_of_iterations[$k] = 0;
    }
  
  if ($is_heuristic_mode == 2)
    {
      $argument_t2 = " -tl " . $TIME_LIMIT . " ";   # heuristic mode 2
    }
  
  foreach (1..$repeticoes)
    {

      my $best_solution = 1000000;   # infinity
      my @minimum_of_solvers;

      my $j = $_;   # LEMBRETE: a lista de arquivos comeca pelo indice zero!
    
      if ($is_W_operator)
	{
	  printf OUT5 "%s     ",  $arquivo[$j-1];
	}

      for (my $k = 0; $k < $number_of_solvers; $k++)
	{
	  my ($t0, $t1);
	  my $current_solver = lc $solvers[$k];
	  # print "\nTeste com %s\n", $solvers[$k];
	  $t0 = [gettimeofday];
    if ($ k == 0)
    {
	      system ("./bin/featsel $window_size -a " . $current_solver . " -c $funcao -d 50 -f input/" . $arquivo[$j-1]  . $argument_t2 . " > result.log");
    }
    else  
    {
        system ("./bin/featsel $window_size -a " . $current_solver . " -c $funcao -f input/" . $arquivo[$j-1]  . $argument_t2 . " > result.log");
	  }
    $t1 = [gettimeofday];
	  $average_time_of_solver[$k] += tv_interval ($t0, $t1);    
	  open (ARQ, "result.log");
	  while (<ARQ>)
	  {
	      if ($_ =~ /(\<\d+\>)\s+\:\s+(\S+)/)
		{
		  if ($is_W_operator)
		    {
		      print OUT5 $1 . " : " . $2 . " | ";
		    }
		  $minimum_of_solvers[$k] = $2;
		}
	      elsif ($_ =~ /^Number\s+of\s+visited\s+subsets\:\s+(\S+)/)
		{ 
		  $average_calls_of_cost_function[$k] += $1;
		}
	      elsif ($_ =~ /subsets\:\s+(\d+)\s+microseconds/)
		{
		  $average_time_of_cost_function[$k] += $1;
		}
	      elsif ($_ =~ /^Number\s+of\s+calls\s+of\s+the\s+minima\s+exhausting\:\s+(\d+)/)
		{   
		  $average_calls_DFS[$k] += $1;
		}
	      elsif ($_ =~ /during\s+the\s+minima\s+exhausting\:\s+(\d+)/)
		{
		  $average_graph_size[$k] += $1;
		}
	      elsif ($_ =~ /is\s+computed\:\s+(\d+)/)
		{
		  $average_calls_minimal_maximal[$k] += $1;
		}
	      elsif ($_ =~ /forest\s+A\:\s+(\d+)/)
		{
		  $average_forest_A_size[$k] += $1;
		}
	      elsif ($_ =~ /forest\s+B\:\s+(\d+)/)
		{
		  $average_forest_B_size[$k] += $1;
		}
	      elsif ($_ =~ /iterations\s+of\s+the\s+main\s+algorithm\:\s+(\d+)/)
		{
		  $average_number_of_iterations[$k] += $1;
		}
        elsif ($_ =~ /time\s+updating\s+restrictions\s+\(in\s+microseconds\)\:\s+(\S+)/)
    {
      $average_restriction_update_time[$k] += $1;
    }
        elsif ($_ =~ /time\s+consulting\s+restrictions\s+\(in\s+microseconds\)\:\s+(\S+)/)
    {
      $average_restriction_consult_time[$k] += $1;
    }
        elsif ($_ =~ /time\s+reducing\s+restrictions\s+\(in\s+microseconds\)\:\s+(\S+)/)
    {
      $average_restriction_reduce_time[$k] += $1;
    } 
        elsif ($_ =~ /^Updates\s+to\s+restrictions\:\s+(\S+)/)
    {
      $average_restriction_update[$k] += $1;
    }
       elsif ($_ =~ /^Consults\s+to\s+restrictions\:\s+(\S+)/)
    {
      $average_restriction_consult[$k] += $1;
    }
      # Toda vez que rodarmos o ucsr7 temos que rodá-lo de novo testando reordenações na ROBDD
    elsif ($_ =~ /^Maximum\s+size\s+of\s+the\s+ROBDD\:\s+(\S+)/ and $current_solver eq "ucsr7")
    {
      $restriction_max0 = $1;
      
      # print "\n Com zero: " . $_;
      # d = 1
      #system ("./bin/featsel $window_size -a " . $current_solver . " -c $funcao -d 1 -f input/" . $arquivo[$j-1]  . $argument_t2 . " > result.log");
      open (ARQ2, "result.log");
      while (<ARQ2>)
      {
        if ($_ =~ /^Maximum\s+size\s+of\s+the\s+ROBDD\:\s+(\S+)/)
        {
          # print "\n Com 1: " . $_;
          $average_restriction_red1 += ($restriction_max0 - $1) / $restriction_max0;
        }
      }
      close (ARQ2);

      # d = 100
      #system ("./bin/featsel $window_size -a " . $current_solver . " -c $funcao -d 100 -f input/" . $arquivo[$j-1]  . $argument_t2 . " > result.log");
      open (ARQ2, "result.log");
      while (<ARQ2>)
      {
        if ($_ =~ /^Maximum\s+size\s+of\s+the\s+ROBDD\:\s+(\S+)/)
        {
          # print "\n Com 100: " . $_;
          $average_restriction_red100 += ($restriction_max0 - $1) / $restriction_max0;
        }
      }
      close (ARQ2);
    }
    }
    close(ARQ);




    if ($is_heuristic_mode == 2)
      {
        printf OUT7 $solvers[$k] . " " . $minimum_of_solvers[$k] . "\n";
      }

    if ($best_solution > $minimum_of_solvers[$k])
      {
        $best_solution = $minimum_of_solvers[$k];
      }
  } 
      
    

      for (my $k = 0; $k < $number_of_solvers; $k++)
  {
    if ($minimum_of_solvers[$k] == $best_solution)
      {
        $number_of_times_that_has_a_best_solution[$k]++;
      }
    elsif ( ($is_heuristic_mode == 0) &&
                  (($solvers[$k] eq "UCS") || ($solvers[$k] eq "UCS2a") ||  ($solvers[$k] eq "UCS2b") ||  ($solvers[$k] eq "PFS") ) )
      {
        printf "\n%s did not find a minimum: %3.2f  :-P~\n\n", $solvers[$k], $minimum_of_solvers[$k];
        system ("cp input/" . $arquivo[$j-1] . " teste_com_erro_no_" . $solvers[$k] . "_" . $i . "_elements.xml");
        exit 0;
      }
  }

      if ($is_W_operator)
  {
    print OUT5 "\n";
  }
      
    } # foreach(1..$repeticoes)
  
  $average_restriction_red100 /= $repeticoes;
  $average_restriction_red1 /= $repeticoes;

  # print "\navg0: " . $restriction_max0 . " | avgred1: " . $average_restriction_red1 . " | avgred100: " . $average_restriction_red100;

  ################################################################################################
  ################################################################################################
    
  # Size of the instance
  printf OUT "<TR><TD><CENTER>&nbsp;%2d&nbsp;</CENTER></TD>", $i;
  printf OUT  "<TD><CENTER>&nbsp;%7d&nbsp;</CENTER></TD>", 2 ** $i;
  printf OUT2 "%2d & ", $i;
  printf OUT2 "%7d & ", 2 ** $i;

  for (my $k = 0; $k < $number_of_solvers; $k++)
    {
      $average_restriction_update_time[$k] /= ($repeticoes * 1000000);
      $average_restriction_consult_time[$k] /= ($repeticoes * 1000000);
      $average_restriction_reduce_time[$k] /= ($repeticoes * 1000000);
      $average_restriction_update[$k] /= $repeticoes;
      $average_restriction_consult[$k] /= $repeticoes;

      $average_calls_of_cost_function[$k] /= $repeticoes;	 
      $average_time_of_cost_function[$k] /= ($repeticoes * 1000000);
      $average_time_of_solver[$k] /= $repeticoes;
      # $number_of_times_that_has_a_best_solution[$k] = ($number_of_times_that_has_a_best_solution[$k] / $repeticoes) * 100;  # uncomment this for a percentage

      $average_calls_DFS[$k] /= $repeticoes;                
      $average_graph_size[$k] /= $repeticoes;
      $average_calls_minimal_maximal[$k] /= $repeticoes; 
      $average_forest_A_size[$k] /= $repeticoes;
      $average_forest_B_size[$k] /= $repeticoes;
      $average_number_of_iterations[$k] /= $repeticoes;

      $tempo_total{$solvers[$k]}->[$i] = $average_time_of_solver[$k];
      if ($average_time_of_solver[$k] > $max_time){    # max_time e' usado para setar a escala do eixo y dos graficos,
	     $max_time = $average_time_of_solver[$k];       # permitindo assim a comparacao entre diferentes graficos
      }
      $tempo_funcao_custo{$solvers[$k]}->[$i] = $average_time_of_cost_function[$k];
      
      if (($solvers[$k] eq "UCS") || ($solvers[$k] eq "UCS2a") ||  ($solvers[$k] eq "UCS2b") )
	{
	  printf OUT3 "%s        %6d          %4.2f          %5.2f          %5.2f          %5.2f          %5.2f\n", $solvers[$k], 2 ** $i,
	    $average_time_of_solver[$k], $average_calls_of_cost_function[$k],
	      $average_graph_size[$k], $average_calls_DFS[$k], $average_calls_minimal_maximal[$k];
	}
      elsif ($solvers[$k] eq "PFS")
	{
	  printf OUT6 "%6d          %4.2f          %5.2f          %5.2f          %5.2f          %5.2f\n", 2 ** $i,
	    $average_time_of_solver[$k], $average_calls_of_cost_function[$k],
	      $average_forest_A_size[$k], $average_forest_B_size[$k], $average_number_of_iterations[$k];
	}
      
    }
  
  # Total Time
  printf OUT "<TD><CENTER>&nbsp;</CENTER></TD>\n";
  for (my $k = 0; $k < $number_of_solvers; $k++)
    {
      printf OUT "<TD><CENTER>&nbsp;%4.2f&nbsp;</CENTER></TD>", $average_time_of_solver[$k];
      printf OUT2 "& %4.2f ", $average_time_of_solver[$k];
    }
  # Cost Function Time
  printf OUT "<TD><CENTER>&nbsp;</CENTER></TD>\n";
  for (my $k = 0; $k < $number_of_solvers; $k++)
    {
      printf OUT "<TD><CENTER>&nbsp;%4.2f&nbsp;</CENTER></TD>", $average_time_of_cost_function[$k];
    }
#entrei aqui
  # Time updating restrictions
  printf OUT "<TD><CENTER>&nbsp;</CENTER></TD>\n";
  for (my $k = 0; $k < 4; $k++)
    {
      printf OUT "<TD><CENTER>&nbsp;%4.2f&nbsp;</CENTER></TD>", $average_restriction_update_time[$k];
    }
  
  # Time reducing restrictions
  printf OUT "<TD><CENTER>&nbsp;</CENTER></TD>\n";
  for (my $k = 0; $k < 4; $k++)
    {
      printf OUT "<TD><CENTER>&nbsp;%4.2f&nbsp;</CENTER></TD>", $average_restriction_reduce_time[$k];
    }
  
  # Restriction Reduction 
  printf OUT "<TD><CENTER>&nbsp;</CENTER></TD>\n";
  printf OUT "<TD><CENTER>&nbsp;%4.2f&nbsp;</CENTER></TD>", $average_restriction_red1;
  printf OUT "<TD><CENTER>&nbsp;%4.2f&nbsp;</CENTER></TD>", $average_restriction_red100;
  
  #Time consulting
  printf OUT "<TD><CENTER>&nbsp;</CENTER></TD>\n";
  for (my $k = 0; $k < 4; $k++)
    {
      printf OUT "<TD><CENTER>&nbsp;%4.2f&nbsp;</CENTER></TD>", $average_restriction_consult_time[$k];
    }
  
  # # of restriction updates
  printf OUT "<TD><CENTER>&nbsp;</CENTER></TD>\n";
  for (my $k = 0; $k < 4; $k++)
    {
      printf OUT "<TD><CENTER>&nbsp;%4.2f&nbsp;</CENTER></TD>", $average_restriction_update[$k];
    }

  # # of restriction consults  
  printf OUT "<TD><CENTER>&nbsp;</CENTER></TD>\n";
  for (my $k = 0; $k < 4; $k++)
    {
      printf OUT "<TD><CENTER>&nbsp;%4.2f&nbsp;</CENTER></TD>", $average_restriction_consult[$k];
    }
#sai aqui
 
  # # of computed nodes
  printf OUT "<TD><CENTER>&nbsp;</CENTER></TD>\n";
  for (my $k = 0; $k < $number_of_solvers; $k++)
    {
      printf OUT "<TD><CENTER>&nbsp;%5.2f&nbsp;</CENTER></TD>", $average_calls_of_cost_function[$k];
      printf OUT2 "& %5.2f ", $average_calls_of_cost_function[$k];
    }

  # # of best solutions found  
  printf OUT "<TD><CENTER>&nbsp;</CENTER></TD>\n";
  for (my $k = 0; $k < $number_of_solvers; $k++)
    {
      printf OUT "<TD><CENTER>&nbsp;%d&nbsp;</CENTER></TD>", $number_of_times_that_has_a_best_solution[$k];
      printf OUT2 "& %d ", $number_of_times_that_has_a_best_solution[$k];
    }
  print OUT "</TR>\n";
  print OUT2 "\\\\ \n";

  print "[done]\n";

} # foreach ...



# Processamento final dos outputs
#

print OUT "</TABLE><BR><HR>\n";
print OUT "
<p>
    <a href=\"http://validator.w3.org/check?uri=referer\"><img
        src=\"http://www.w3.org/Icons/valid-html401-blue\"
        alt=\"Valid HTML 4.01 Strict\" height=\"31\" width=\"88\"></a>
</p>\n";
print OUT "</BODY></HTML>\n";
close (OUT);


print OUT2  "\\bottomrule \\end{tabular} \\caption{Caption text} \\label{tab:comparison} \\end{center} \\end{table}" . "\n";
close (OUT2);


close (OUT3);


if ($is_heuristic_mode == 1)
  {
    print OUT4  "\\bottomrule \\end{tabular} \\caption{Caption text heuristic} \\label{tab:comparison_heuristic} \\end{center} \\end{table}" . "\n";
    close (OUT4);
  }

if ($is_heuristic_mode == 2)
  {
    close (OUT7);
  }

close (OUT5);
close (OUT6);

#
# agora imprime os graficos do gnuplot
#

foreach my $algo (@solvers){

  open (INPUT, ">dat.temp");
  if (!$is_W_operator){
    printf INPUT "0 0 0\n";
    for (my $i = 1; $i <= $n; $i++){
      printf INPUT "$i %.4f %.4f\n", $tempo_funcao_custo{$algo}->[$i], $tempo_total{$algo}->[$i];
    }
  }
  else{
    foreach my $i (@experiments){
      printf INPUT "$i %.4f %.4f\n", $tempo_funcao_custo{$algo}->[$i], $tempo_total{$algo}->[$i] - $tempo_funcao_custo{$algo}->[$i];
    }
    $n = scalar @experiments;
  }
  close (INPUT);

  my $Xaxis = 35 * $n;

  open (PLOT, ">output/gnuplot.temp");
#  printf PLOT "set terminal png transparent nocrop enhanced size $Xaxis,320\n";
  printf PLOT "set terminal postscript\n";
  printf PLOT "set output 'output/$algo\_$saida.eps'\n";
  printf PLOT "unset key\n";

  if ($is_W_operator){
#    printf PLOT "set terminal png transparent nocrop enhanced size 420,320\n";
    printf PLOT "set boxwidth 0.75 absolute\nset style fill solid 1.00 border -1\n";
    printf PLOT "set style histogram rowstacked\nset style data histograms\n";
    printf PLOT "set ylabel \"Time (seconds)\"\nset xlabel \"Experiment number\"\n";
    printf PLOT "set yrange [0: $max_time]\n";
#    printf PLOT "set xrange [0.5:$n+0.5]\n";
    printf PLOT "plot 'dat.temp' using 2 t \"Cost Function\", '' using 3:xtic(1) t \"Control\"\n";
  }

  else{
    printf PLOT "set xlabel \"|S|\"\nset ylabel \"Time (seconds)\"\n";
    printf PLOT "set xtics (\"0\" 0";
    foreach my $i (@experiments){
      printf PLOT ", \"$i\" $i";
    }
    printf PLOT ")\n";
    printf PLOT "unset colorbox\n";
    printf PLOT "set style line 1 lt 2 lc rgb \"red\" lw 1\n";
    printf PLOT "set style line 2 lt 2 lc rgb \"blue\" lw 2\n";
    printf PLOT "plot \"dat.temp\" using 2 t \"Cost Function\" with lines ls 1, '' using 3:xtic(1) t \"Control\" with lines ls 2\n";
  }

  close (PLOT);
  system ("gnuplot output/gnuplot.temp");

}


#
# encerra a bateria de testes
#
system ("rm result.log");
system ("rm output/*.temp");
system ("rm *.temp");

if (! $is_W_operator)
  {
    system ("rm input/*.xml");
  }

exit 0;
