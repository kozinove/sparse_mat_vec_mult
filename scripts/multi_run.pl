use List::Util qw( min max );

$arg = join( ' ', @ARGV);

@times = ();
for($i = 0; $i < 2; $i++)
{
  $res = `$arg`;
  if ($res =~ /n: (.+)\n/)
  {
    $n = $1;
  }
  if ($res =~ /nz: (.+)\n/)
  {
    $nz = $1;
  }
  
  if ($res =~ /(.+): (.+)([ ]*s)\n/)
  {
    $str1 = $1;
    $time = $2;
    $str2 = $3;
  }
  
  $err = "";
  
  if($res =~ /MULT_ERROR/)
  {
    $err = "MULT_ERROR";
  }

#  print "$str1|$time|$str2\n";
  
  $time = $time * 1.0;
  @times = ($time, @times);
}

$min_time = min @times;

#print $str1.": ".$min_time.$str2."\n";
print "$n\t$nz\t$min_time\t$err";
