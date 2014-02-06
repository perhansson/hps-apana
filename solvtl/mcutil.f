c-----------------------------------------------------------------------
c     Inverse of the hyperbolic cosine (N.R. s. 178)
c
      function acosh(x)
c-----------------------------------------------------------------------
      implicit none
      real*8 acosh,x
      if (x.lt.1d0) then
         print *,'acosh argument out of valid range: ',x
         stop
      endif
      acosh=dlog(x+dsqrt(x**2-1))
      end

c-----------------------------------------------------------------------
      subroutine stats(mode,val,mean,rms,max,samp,n)
c-----------------------------------------------------------------------
      implicit none
      integer mode,n,samp,i
      real*8 val(*),mean(*),rms(*),max(*)

      if (mode.eq.-1) then
         samp=0
         do i=1,n
            mean(i)=0.d0
            rms(i)=0.d0
            max(i)=0.d0
         enddo
      elseif(mode.eq.0) then
         do i=1,n
            mean(i)=mean(i)+val(i)
            rms(i)=rms(i)+val(i)*val(i)
            if (abs(val(i)).gt.abs(max(i))) max(i)=val(i)
         enddo
         samp=samp+1
      elseif(mode.eq.1) then
         print *,'********************************'
         print *,'*  value#    Mean   RMS  MAX   *'
         print *,'********************************'
         do i=1,n
            mean(i)=mean(i)/dble(samp)
            rms(i)=sqrt((rms(i)/dble(samp)-mean(i)**2)/dble(samp-1))
            print *,i,real(mean(i)),real(rms(i)),real(max(i))
         enddo
      else
         print *,'unknown stats mode.'
         stop
      endif

      end

c-----------------------------------------------------------------------
      subroutine boost(P,R,Q)
c-----------------------------------------------------------------------
      implicit none
      real*8  P(4),R(4),Q(4)
      real*8  BETA(3), X, Y, GAMMA
      integer i

      X = 0.
      Y = 0.
      do i = 1,3
         BETA(i) = R(i)/R(4)
         X = X + BETA(I)**2
         Y = Y + BETA(I)*P(I)
      enddo
      if ( X.lt.1e-8 .and. X.ge.(1. - 1e-8) ) GOTO 30
      GAMMA = 1./sqrt(1.-X)
      do I = 1,3
         Q(I) = P(I)+GAMMA*BETA(I)*(Y*GAMMA/(GAMMA+1) + P(4))
      enddo
      Q(4) = GAMMA*(P(4) + Y)
      return
   30 continue
      do I = 1,4
         Q(I) = P(I)
      enddo
      if ( X.ge.(1. - 1e-8) ) 
     &   write(6,1000) R,R(4)**2 - R(1)**2 - R(2)**2 - R(3)**2
      return
 1000 format (' The reference vector ',4G12.3,' is not timelike.'/
     &        ' R**2 = ',G12.3)

      end

c-----------------------------------------------------------------------
      subroutine calce(a,m2,b)
c-----------------------------------------------------------------------
      implicit none
      real*8 a(4),m2,b(4)

      b(4)=sqrt(a(1)**2+a(2)**2+a(3)**2+m2)

      end
      
c-----------------------------------------------------------------------
      subroutine mkdcy2(p1,s2,s3,p2,p3)
c-----------------------------------------------------------------------
      implicit none
      real*8 q2,p1(4),p2(4),p3(4),s2,s3,k,phi,theta
      real*8 pi
      parameter (pi=3.141592653589793238d0)
      real*8 pyr

      q2=p1(4)**2-p1(1)**2-p1(2)**2-p1(3)**2
      if (q2.le.(sqrt(s2)+sqrt(s3))**2) then
         print *,'Decay cannot proceed: ',q2,'->',s2,s3
         stop
      endif
      if (s2.lt.0d0) then
         if (s2.lt.-1d-2) then
            print *,'Very negative s2: ',s2,' stop!'
            stop
         else
            s2=0d0
         endif
      endif
      if (s3.lt.0d0) then ! paranoia
         if (s3.lt.-1d-2) then
            print *,'Very negative s3: ',s3,' stop!'
            stop
         else
            s3=0d0
         endif
      endif

      k=sqrt(((q2-s2-s3)**2-4.d0*s2*s3)/q2)/2.d0
      phi=2.d0*pi*pyr(0)
      call peek(phi,0)
      theta=dacos(1d0-2.d0*pyr(0))
      call peek(theta,0)
      p2(1)=k*dcos(phi)*sin(theta)
      p2(2)=k*dsin(phi)*sin(theta)
      p2(3)=k*dcos(theta)
      p3(1)=-p2(1)
      p3(2)=-p2(2)
      p3(3)=-p2(3)
      call calce(p2,s2,p2)
      call calce(p3,s3,p3)

      call boost(p2,p1,p2)
      call boost(p3,p1,p3)

      end

c-----------------------------------------------------------------------
      subroutine mkdcy4(q,s2,s3,m12,m22,m32,m42,p1,p2,p3,p4)
c-----------------------------------------------------------------------
      implicit none
      real*8 q,s2,s3,m12,m22,m32,m42
      real*8 p1(4),p2(4),p3(4),p4(4),p5(4),p6(4)

      call mkdcy2(q,s2,s3,p5,p6)
      call mkdcy2(p5,m12,m32,p1,p3)
      call mkdcy2(p6,m22,m42,p2,p4)
      
      end

c-----------------------------------------------------------------------
      subroutine mkdcy6(q,s2,s3,s4,s5,m12,m22,m11,m21,p1,p2,p3,p4,p5,p6)
c-----------------------------------------------------------------------
      implicit none
      real*8 q,s2,s3,s4,s5,m12,m22,m11,m21
      real*8 p1(4),p2(4),p3(4),p4(4),p5(4),p6(4)
      real*8 p7(4),p8(4),p9(4),p10(4)

      call mkdcy2(q,s2,s3,p7,p8)
      call mkdcy2(p7,m12,s4,p3,p9)
      call mkdcy2(p8,m22,s5,p4,p10)
      call mkdcy2(p9,m11,0d0,p1,p5)
      call mkdcy2(p10,m21,0d0,p2,p6)
      
      end

c-------------------------------------------------------------
      function g_q(x,e) ! q^2 peek above 2m_t
c-------------------------------------------------------------
      implicit none
      real*8 g_q,x,e
      g_q=x**(-e)
      end

c-------------------------------------------------------------
      function pg_q(x,e) ! Prim function of the q^2 peek
c-------------------------------------------------------------
      implicit none
      real*8 pg_q,x,e
      pg_q=-(x**-(e-1d0))/(e-1d0)
      end

c-------------------------------------------------------------
      function ipg_q(x,e) ! Prim function inv of the q^2 peek
c-------------------------------------------------------------
      implicit none
      real*8 ipg_q,x,e
      ipg_q=(-(e-1d0)*x)**(-1d0/(e-1d0))
      end      

c-------------------------------------------------------------
      function g_s(x,m,w) ! s-channel propagator peek
c-------------------------------------------------------------
      implicit none
      real*8 g_s,x,m,w
      g_s=1.d0/((x-m*m)**2+(w*m)**2)
      end

c-------------------------------------------------------------
      function pg_s(x,m,w) ! Prim function of the s-channel prop peek
c-------------------------------------------------------------
      implicit none
      real*8 pg_s,x,m,w
      pg_s=datan((x-m*m)/(m*w))/(m*w)
      end

c-------------------------------------------------------------
      function ipg_s(x,m,w) ! Prim function inv of the s-channel prop peek
c-------------------------------------------------------------
      implicit none
      real*8 ipg_s,x,m,w
      ipg_s=m*(w*dtan(m*w*x)+m)
      end

c-------------------------------------------------------------
      subroutine peek(val,op)
c-------------------------------------------------------------
      implicit none
      real*8 val
      integer op
      integer n,i
      real*8 store(50)
      save store,n

      return
      if (op.eq.-1) then
         open (20,file='peek.dat',status='unknown')
         n=0
      elseif(op.eq.0) then
         n=n+1
         store(n)=val
      elseif(op.eq.1) then
         write (20,*) (real(store(i)),i=1,n)
         n=0
      elseif(op.eq.2) then
         close (20)
      else
         print *,'Unknown store operation:',op
         stop
      endif
      if (n.gt.50) then
         print *,'Store out of index!'
         stop
      endif
      end
   


