public class ThreadTester
{
  public static void main( String[] args )
  {
    if ( args.length > 0 )
    {
      if ( Integer.parseInt( args[0] ) < 0 )
        System.err.println( args[0] + " must be >= 0.");
      else
      {
        Summation thrd = new Summation( Integer.parseInt( args[0] ) );
        System.out.println("Antes de lanzar el thread");
        thrd.start();
        System.out.println("Después de lanzar el thread");
        try
        {
          thrd.join();
        } catch (InterruptedException e) {
           e.printStackTrace();
        }
        System.out.println("The sum of "+args[0]+" is "+thrd.getSum());
      }
    }
    else
      System.err.println("Usage: Summation <integer value>");
  }
}
