      program add
c
c       John Mahaffy,  Penn State University, CmpSc 201 Example
c       1/26/96
c
c
c   This is a simple program to read 2 numbers and print the sum
c
      implicit none
      real a,b,s
c
c   a - one of two numbers to be added
c   b - the other number in the sum
c   s - the sum of a and b
c
c  Get the numbers from the program user
c  First ask for the numbers
c
      print *, ' This program adds 2 real numbers, 1.0 and 2.5'
      a=1.0
      b=2.5
c
c   Now calculate the sum
c
      s = a + b
c
c   Print out the results with a description
c
20    format ('The sum of ',f6.4,' and ',f6.4,' is ',f6.4)
      write (*,20) a,b,s
c      stop
      end
