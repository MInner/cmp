class Bubble {
  public static void main(String[] a) {
      System.out.println(new BubbleSort().runSort());
  }
}

class BubbleSort
{
  public int runSort(int[] arr) {
      int[] b;
      int tmp;
      b = new int[3]; 
      b[0] = 3;
      b[1] = 1;
      b[2] = 2;
      return this.bubbleSort(b);
  }
  
  public int bubbleSort(int[] arr) {
      bool swapped;
      bool var;
      int j;
      int i;
      int tmp;

      swapped = true;
      j = 1;
      while (swapped) {
            swapped = false;
            j = j + 1;
            i = 0;
            while (i < (arr.length - j) ) {
                if ( arr[i+1] < arr[i] ) {                          
                      tmp = arr[i];
                      arr[i] = arr[i + 1];
                      arr[i + 1] = tmp;
                      swapped = true;
                }
                else
                {}

                i = i + 1;
            }                
      }
      return 0;
  }

    
}

