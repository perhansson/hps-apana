c***************************************************************
c
c C.Clement Modified version (2010-01-31) of 
c Solutions to the neutrino momenta in tt~ -> e+ ne b e- ne~ b~
c Author: sjolin@physto.se
c To allow to extract the imaginary part of the neutrino pz
c***************************************************************

      subroutine solvtlimg(pl1,pl2,pb1,pb2,metx,mety,mt,mw,mb,pn1,pn2,
     &     n,ipnu1,ipnu2)
      implicit none
      real*8 pb1(4),pb2(4),pl1(4),pl2(4),metx,mety,pn1(4,4),pn2(4,4)
      integer n
      real*8 b1,b2,el1,el2,c1,c2,f1,f2
      real*8 d1x,d1y,d1z,d2x,d2y,d2z
      real*8 e2p2x1,e2p2y1,e2p2z1,e2p2x2,e2p2y2,e2p2z2
      real*8 a2x,a2y,a2z,c2x,c2y,c2z
      real*8 e1x,e1y,e1,e2x,e2y,e2
      real*8 aa1,bb1,cc1,dd1,aa2,bb2,cc2,dd2,u1,v1,u2,v2
C      real*8 x1,y1,z1,x2,y2,z2,q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11
      real*8 q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11
      real*8 k4(5)
      complex*16 r4(4)
c     now put x1,y1,z1,x2,y2,z2 as coplex
      complex*16 x1,y1,z1,x2,y2,z2
      integer i
      real*8 mt,mw,mb,mt2,mw2,mb2,plb12,plb22
      real*8 ipnu1(4,4),ipnu2(4,4)

      mt2=mt*mt
      mw2=mw*mw
      mb2=mb*mb
      b1=metx
      b2=mety
c      b1=-(pl1(1)+pl2(1)+pb1(1)+pb2(1))
c      b2=-(pl1(2)+pl2(2)+pb1(2)+pb2(2))
      c1=(mt2-mb2)/2.d0-pl1(4)*pb1(4)+pl1(1)*pb1(1)+pl1(2)*pb1(2)+pl1(3)
     &     *pb1(3)
      c2=(mt2-mb2)/2.d0-pl2(4)*pb2(4)+pl2(1)*pb2(1)+pl2(2)*pb2(2)+pl2(3)
     &     *pb2(3)
      el1=(pl1(4)+pb1(4))/pl1(4)
      el2=(pl2(4)+pb2(4))/pl2(4)
      f1=c1-mw2*el1/2.d0
      f2=c2-mw2*el2/2.d0

      d1x=(el1-1.d0)*pl1(1)-pb1(1)
      d1y=(el1-1.d0)*pl1(2)-pb1(2)
      d1z=(el1-1.d0)*pl1(3)-pb1(3)
      d2x=(el2-1.d0)*pl2(1)-pb2(1)
      d2y=(el2-1.d0)*pl2(2)-pb2(2)
      d2z=(el2-1.d0)*pl2(3)-pb2(3)

      e1x=-d1x/d1z
      e1y=-d1y/d1z
      e1=f1/d1z
      e2x=d2x/d2z
      e2y=d2y/d2z
      e2=(f2-d2x*b1-d2y*b2)/d2z

      e2p2x1=pl1(4)*pl1(4)-pl1(1)*pl1(1)
      e2p2y1=pl1(4)*pl1(4)-pl1(2)*pl1(2)
      e2p2z1=pl1(4)*pl1(4)-pl1(3)*pl1(3)
      e2p2x2=pl2(4)*pl2(4)-pl2(1)*pl2(1)
      e2p2y2=pl2(4)*pl2(4)-pl2(2)*pl2(2)
      e2p2z2=pl2(4)*pl2(4)-pl2(3)*pl2(3)

      aa1=e2p2x1+(e2p2z1*e1x-2.d0*pl1(1)*pl1(3))*e1x
      cc1=e2p2y1+(e2p2z1*e1y-2.d0*pl1(2)*pl1(3))*e1y
      bb1=2.d0*(e2p2z1*e1x*e1y-pl1(1)*pl1(2)-pl1(1)*pl1(3)*e1y-
     &     pl1(2)*pl1(3)*e1x)
      u1=2.d0*(e2p2z1*e1x*e1-pl1(1)*pl1(3)*e1)-mw2*(pl1(1)+pl1(3)*e1x)
      v1=2.d0*(e2p2z1*e1y*e1-pl1(2)*pl1(3)*e1)-mw2*(pl1(2)+pl1(3)*e1y)
      dd1=e2p2z1*e1*e1-mw2*mw2/4.d0-mw2*pl1(3)*e1

      aa2=e2p2y2+(e2p2z2*e2y+2.d0*pl2(2)*pl2(3))*e2y
      cc2=e2p2x2+(e2p2z2*e2x+2.d0*pl2(1)*pl2(3))*e2x
      bb2=2.d0*(e2p2z2*e2x*e2y-pl2(1)*pl2(2)+pl2(1)*pl2(3)*e2y+
     &     pl2(2)*pl2(3)*e2x)
      u2=2.d0*(-b2*e2p2y2+e2y*e2*e2p2z2+b1*pl2(1)*pl2(2)-
     &     b1*e2y*pl2(1)*pl2(3)-b2*e2y*pl2(2)*pl2(3)+e2*pl2(2)*pl2(3))+
     &     mw2*(pl2(2)-pl2(3)*e2y)
      v2=2.d0*(-b1*e2p2x2+e2x*e2*e2p2z2+b2*pl2(1)*pl2(2)-
     &     b1*e2x*pl2(1)*pl2(3)-b2*e2x*pl2(2)*pl2(3)+e2*pl2(1)*pl2(3))+
     &     mw2*(pl2(1)-pl2(3)*e2x)
      dd2=e2p2x2*b1*b1+e2p2y2*b2*b2+e2p2z2*e2*e2-mw2*mw2/4.d0-
     &     2.d0*(pl2(1)*pl2(2)*b1*b2+pl2(1)*pl2(3)*b1*e2+
     &     pl2(2)*pl2(3)*b2*e2)-mw2*(pl2(1)*b1+pl2(2)*b2+pl2(3)*e2)

      q1=aa2
      q2=bb2
      q3=cc2
      q4=dd2
      q5=u2
      q6=v2
      q7=cc1*cc2-aa1*aa2
      q8=cc1*v2-aa2*u1
      q9=cc1*dd2-aa2*dd1
      q10=aa2*bb1-bb2*cc1
      q11=aa2*v1-cc1*u2

      k4(1)=q1*q7*q7+q2*q7*q10+q3*q10*q10
      k4(2)=2.d0*q1*q7*q8+q2*q8*q10+q2*q7*q11+2.d0*q3*q10*q11+
     &     q6*q10*q10+q5*q7*q10
      k4(3)=q1*q8*q8+2*q1*q7*q9+q2*q9*q10+q2*q8*q11+q3*q11*q11+
     &     q4*q10*q10+2.d0*q6*q10*q11+q5*q7*q11+q5*q8*q10
      k4(4)=2.d0*q1*q8*q9+q2*q9*q11+2.d0*q4*q10*q11+q6*q11*q11+
     &     q5*q8*q11+q5*q9*q10
      k4(5)=q1*q9*q9+q4*q11*q11+q5*q9*q11
      
      call solv4x(k4,r4)

      n=0
      do i=1,4
         n=n+1
         x1=r4(i)
         y1=(q7*x1*x1+q8*x1+q9)/(q10*x1+q11)
         z1=e1x*x1+e1y*y1+e1
         x2=b1-x1
         y2=b2-y1
         z2=e2x*x1+e2y*y1+e2
         
         pn1(1,n)=dreal(x1)
         pn1(2,n)=dreal(y1)
         pn1(3,n)=dreal(z1)
         pn1(4,n)=sqrt(dreal(x1)*dreal(x1)+dreal(y1)*dreal(y1)+
     &        dreal(z1)*dreal(z1))

         pn2(1,n)=dreal(x2)
         pn2(2,n)=dreal(y2)
         pn2(3,n)=dreal(z2)
         pn2(4,n)=sqrt(dreal(x2)*dreal(x2)+dreal(y2)*dreal(y2)+
     &        dreal(z2)*dreal(z2))

         ipnu1(1,n)=dimag(x1)
         ipnu1(2,n)=dimag(y1)
         ipnu1(3,n)=dimag(z1)
         ipnu1(4,n)=sqrt(dimag(x1)*dimag(x1)+dimag(y1)*dimag(y1)+
     &        dimag(z1)*dimag(z1))

         ipnu2(1,n)=dimag(x2)
         ipnu2(2,n)=dimag(y2)
         ipnu2(3,n)=dimag(z2)
         ipnu2(4,n)=sqrt(dimag(x2)*dimag(x2)+dimag(y2)*dimag(y2)+
     &        dimag(z2)*dimag(z2))

      enddo
      
      end
