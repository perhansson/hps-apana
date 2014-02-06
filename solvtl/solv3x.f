c*******************************************************
c*
c* Solve cubic equation (NR p.179)
c*
c*   input  a(4): k3(1)*x^3+k3(2)*x^2+k3(3)*x+k3(4)=0
c*   output r(3): roots
c*
c*******************************************************
      subroutine solv3x(k3,r3)
      implicit none
      real*8 k3(4)
      complex*16 r3(3)
      real*8 pi
      parameter (pi=3.141592653589793238d0)
      real*8 a,b,c,q,r,sqrq,theta,aa,bb
      real*8 a2,a3,r2,q3
      
      if (k3(1).eq.0) then
         print *,'k3(1)=0, stop.'
         stop
      endif

      a=k3(2)/k3(1)
      b=k3(3)/k3(1)
      c=k3(4)/k3(1)
      
      a2=a*a
      a3=a*a2
      q=(a2-3.d0*b)/9.d0
      r=(2.d0*a3-9.d0*a*b+27.d0*c)/54.d0

      r2=r*r
      q3=q*q*q
      if (q3.gt.r2) then
         theta=acos(r/sqrt(q3))
         sqrq=sqrt(q)
         r3(1)=-2.d0*sqrq*cos(theta/3.d0)-a/3.d0
         r3(2)=-2.d0*sqrq*cos((theta+2.d0*pi)/3.d0)-a/3.d0
         r3(3)=-2.d0*sqrq*cos((theta-2.d0*pi)/3.d0)-a/3.d0
      else
         aa=-sign((abs(r)+sqrt(r2-q3))**(1./3.d0),r)
         if (aa.eq.0) then
            bb=0.d0
         else
            bb=q/aa
         endif
         r3(1)=(aa+bb)-a/3.d0
         r3(2)=-(aa+bb)/2.d0-a/3.d0+(0.d0,1.d0)*sqrt(3.d0)*(aa-bb)/2.d0
         r3(3)=-(aa+bb)/2.d0-a/3.d0-(0.d0,1.d0)*sqrt(3.d0)*(aa-bb)/2.d0
      endif
         
      end
