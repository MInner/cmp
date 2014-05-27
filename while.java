class Bubble {
  public static void main(String[] a) {
      System.out.println(new BubbleSort().runSort());
  }
}

class BubbleSort
{
  public int runSort() {
      int c;
      c = 10;
      while( c < 20 )
      {
        if (c < 15)
        {
          c = c + 1;
        }
        else
        {
          if ( c < 17 )
          {
            c = c + 3;
          }
          else
          {
            c = c + 4;
          }
        }
      }
      return 0;
  }
    
}

