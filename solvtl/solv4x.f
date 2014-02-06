c*******************************************************
c*
c* Solve quartic equation (The Leonard Euler style)
c*
c*   input  a(4): k(1)*x^4+k(2)*x^3+k(3)*x^2+k(4)*x+k(5)=0
c*   output r(4): roots
c*
c*******************************************************
      subroutine solv4x(k4,r4)
      implicit none
      real*8 k4(5)
      complex*16 r4(4)
      real*8 k3(4)
      complex*16 r3(3)
      real*8 a,b,c,d,e,f,g,a2,a3,a4
      complex*16 p,q,r
      complex*16 fx,fxp,h
      integer i

      if (k4(1).eq.0) then
         print *,'k4(1)=0, stop.'
         stop
      endif
      
      a=k4(2)/k4(1)
      b=k4(3)/k4(1)
      c=k4(4)/k4(1)
      d=k4(5)/k4(1)

      a2=a*a
      a3=a*a2
      a4=a*a3
      e=b-3.d0*a2/8.d0
      f=c+a3/8.d0-a*b/2.d0
      g=d-3.*a4/256.d0+a2*b/16.d0-a*c/4.d0

      if (g.eq.0) then
         print *,'g=0 not handled, stop.'
         stop
      endif

      if (f.eq.0) then
         print *,'f=0 not handled, stop.'
         stop
      endif

      k3(1)=1.d0
      k3(2)=e/2.d0
      k3(3)=(e*e-4.*g)/16.d0
      k3(4)=-f*f/64.d0

      call solv3x(k3,r3)
      
      p=sqrt(r3(1))
      q=sqrt(r3(2))
      r=-f/(8.d0*p*q)
      r4(1)=p+q+r-a/4.d0
      r4(2)=p-q-r-a/4.d0
      r4(3)=-p+q-r-a/4.d0
      r4(4)=-p-q+r-a/4.d0

c      do i=1,4
c         fx=k4(1)*r4(i)**4+k4(2)*r4(i)**3+k4(3)*r4(i)**2+k4(4)*r4(i)+
c     &        k4(5)
c         fxp=4*k4(1)*r4(i)**3+3*k4(2)*r4(i)**2+2*k4(3)*r4(i)+k4(4)
c         h=-fx/fxp
c         r4(i)=r4(i)+h
c         print *,'h=',h
c      enddo
      

      end




