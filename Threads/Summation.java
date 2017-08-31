class Summation extends Thread
{
  private int upper, sum=0;

  public Summation( int n )
  {
    upper = n;
  }

  public int getSum()
  {
    return sum;
  }

  public void run()
  {
    if ( upper > 0 )
    {
      for ( int i=1; i<=upper; i++ )
        sum += i;
    }
  }
}
