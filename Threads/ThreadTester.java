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
        Summation threads[] = new Summation[ Integer.parseInt(args[0]) ];

        for (int i=0; i<Integer.parseInt(args[0]); i++)
        {
          threads[i] = new Summation( i+1 );
          System.out.println("Antes de lanzar el thread"+(i+1));
          threads[i].start();
          System.out.println("Después de lanzar el thread"+(i+1));

          try
          {
            threads[i].join();
          } catch (InterruptedException e) {
             e.printStackTrace();
          }
          System.out.println("The sum of "+(i+1)+" is "+threads[i].getSum());

        }
      }
    }
    else
      System.err.println("Usage: Summation <integer value>");
  }
}
