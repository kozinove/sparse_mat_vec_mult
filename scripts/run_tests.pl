use File::Basename;
my @files = grep { !/_coord\.mtx$/ } grep { !/\_.\.mtx$/ } glob("mat/*/*.mtx" );


open(OUT, ">>res.csv");

$cnt_th = $ENV{"OMP_NUM_THREADS"};
$cnt_rep = $ARGV[0];

print "threads\t$cnt_th\tcnt_rep\t$cnt_rep\n";
print "threads\t$cnt_th\tcnt_rep\t$cnt_rep\n";

foreach $mat (@files)
{
  print $mat."\n";
  $run = "perl multi_run.pl ./mkl_run/mkl_mv $mat $cnt_rep";
  $res = `$run`;
  $name = basename($mat);
  print "$name\t$res\n";
  print OUT "$name\t$res\n";
}

close(OUT);