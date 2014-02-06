      subroutine calcv(p1,p2,p3,p4,p5,metx,mety,V)
      implicit none
      include 'scale.inc'
      real*8 p1(4),p2(4),p3(4),p4(4),p5(4),metx,mety,V(Neta,Neta)
      integer i,j

      do i=1,Neta
         do j=1,Neta
            V(i,j)=0.
c            if (i.eq.j) V(i,j)=10.
         enddo
      enddo

      do i=1,3
         V(i   ,   i)=(0.1d0)**2*p1(4)/3d0
         V(i+ 3,i+ 3)=(0.5d0)**2*p2(4)/3d0
         V(i+ 6,i+ 6)=(0.5d0)**2*p3(4)/3d0
         V(i+ 9,i+ 9)=(0.5d0)**2*p4(4)/3d0
         V(i+12,i+12)=(0.5d0)**2*p5(4)/3d0
      enddo
      V(16,16)=10d0**2
      V(17,17)=10d0**2
      V(18,18)=10d0**2
      V(19,19)=10d0**2
      V(20,20)=3d0**2+0.5d0**2*dsqrt(metx**2+mety**2)/2d0
      V(21,21)=V(20,20)

      end
