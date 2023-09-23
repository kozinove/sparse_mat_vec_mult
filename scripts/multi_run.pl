use List::Util qw( min max );

$arg = join( ' ', @ARGV);

@times = ();
for($i = 0; $i < 5; $i++)
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
  
  if ($res =~ /min_elem : (.+)\n/)
  {
    $min_elem = $1;
  }
  if ($res =~ /max_elem : (.+)\n/)
  {
    $max_elem = $1;
  }
  if ($res =~ /q : (.+)\n/)
  {
    $q = $1;
  }
  if ($res =~ /avg : (.+)\n/)
  {
    $avg = $1;
  }

#  print "$str1|$time|$str2\n";
  
  $time = $time * 1.0;
  @times = ($time, @times);
}

$min_time = min @times;

#print $str1.": ".$min_time.$str2."\n";
print "$n\t$nz\t$min_time\t$min_elem\t$max_elem\t$avg\t$q\t$err";
