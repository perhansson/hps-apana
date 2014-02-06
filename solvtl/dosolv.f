      program dosolv
      implicit none
      real*8 q(4),p1(4),p2(4),p3(4),p4(4),p5(4),p6(4)
      integer i,n,k
      real*8 pn1(4,4),pn2(4,4),pa(4),pb(4)
      real d1,d2
      real*8 mt2,mw2,plb12,plb22
      real*8 mt,mw,mb,mb2
      parameter (mt=174.3d0,mw=79.95477d0,mb=5.d0)
      parameter (mt2=mt*mt,mw2=mw*mw,mb2=mb*mb)
      real*8 val(10),mean(10),rms(10),max(10)
      integer samp,event,class(0:9),sol
      real*8 cosa,cosb,p1p2,pp1,pp2
      real rndm,x

      do k=0,9
         class(k)=0
      enddo

      call stats(-1,val,mean,rms,max,samp,6)
      
      do event=1,1000

         q(1)=0
         q(2)=0
         q(3)=dble(rndm(x))*7000.d0
         q(4)=sqrt(q(3)**2+
     &        (2.d0*(mt+mw+mb+0.01)+7000.d0*dble(rndm(x)))**2)
         
         call mkdcy6(q,mt2,mt2,mw2,mw2,mb2,mb2,
     &        0d0,0d0,p1,p2,p3,p4,p5,p6)

c         do i=1,2
c            print *,'mpt=',p1(i)+p2(i)+p3(i)+p4(i)+p5(i)+p6(i)
c         enddo
         
c         do i=1,4
c            pa(i)=p1(i)+p5(i)
c            pb(i)=p2(i)+p6(i)
c         enddo
c         print *,'mw1=',sqrt(pa(4)**2-pa(1)**2-pa(2)**2-pa(3)**2)
c         print *,'mw2=',sqrt(pb(4)**2-pb(1)**2-pb(2)**2-pb(3)**2)
         
c         do i=1,4
c            pa(i)=pa(i)+p3(i)
c            pb(i)=pb(i)+p4(i)
c         enddo
c         print *,'mt1=',sqrt(pa(4)**2-pa(1)**2-pa(2)**2-pa(3)**2)
c         print *,'mt2=',sqrt(pb(4)**2-pb(1)**2-pb(2)**2-pb(3)**2)
c         print *,'p1',p1
c         print *,'p2',p2
c         print *,'p3',p3
c         print *,'p4',p4
         call solvtl(p1,p2,p3,p4,p5(1)+p6(1),p5(2)+p6(2),mt,mw,mb,
     &        pn1,pn2,n)
c         print *,'event=',event,' solutions=',n
         sol=0
         class(n)=class(n)+1
         if (n.gt.0) then
            do i=1,n

c               do k=1,2
c                  print *,'mpt=',p1(k)+p2(k)+p3(k)+p4(k)+
c     &                 pn1(k,i)+pn2(k,i)
c               enddo
c               
c               do k=1,4
c                  pa(k)=p1(k)+pn1(k,i)
c                  pb(k)=p2(k)+pn2(k,i)
c               enddo
c               print *,'mw1=',sqrt(pa(4)**2-pa(1)**2-
c     &              pa(2)**2-pa(3)**2)
c               print *,'mw2=',sqrt(pb(4)**2-pb(1)**2-
c     &              pb(2)**2-pb(3)**2)
c               
c               do k=1,4
c                  pa(k)=pa(k)+p3(k)
c                  pb(k)=pb(k)+p4(k)
c               enddo
c               print *,'mt1=',sqrt(pa(4)**2-pa(1)**2-pa(2)**2-
c     &              pa(3)**2)
c               print *,'mt2=',sqrt(pb(4)**2-pb(1)**2-pb(2)**2-
c     &              pb(3)**2)
c               
               
               p1p2=p5(1)*pn1(1,i)+p5(2)*pn1(2,i)+p5(3)*pn1(3,i)
               pp1=sqrt(p5(1)**2+p5(2)**2+p5(3)**2)
               pp2=sqrt(pn1(1,i)**2+pn1(2,i)**2+pn1(3,i)**2)
               cosa=p1p2/(pp1*pp2)

               p1p2=p6(1)*pn2(1,i)+p6(2)*pn2(2,i)+p6(3)*pn2(3,i)
               pp1=sqrt(p6(1)**2+p6(2)**2+p6(3)**2)
               pp2=sqrt(pn2(1,i)**2+pn2(2,i)**2+pn2(3,i)**2)
               cosb=p1p2/(pp1*pp2)
               
               if (cosa.gt.(1.d0-1.d-6).and.cosb.gt.(1.d0-1.d-6).and.
     &          p5(1)*pn1(1,i).gt.0.d0.and.p5(2)*pn1(2,i).gt.0.d0.and.
     &          p5(3)*pn1(3,i).gt.0.d0.and.p6(1)*pn2(1,i).gt.0.d0.and.
     &          p6(2)*pn2(2,i).gt.0.d0.and.p6(3)*pn2(3,i).gt.0.d0) then
                 sol=sol+1
                  
c                  print *,'-------------------------------------'
c                  do k=1,4
c                     print *,'(',i,') ','p5,pn1=',p5(k),pn1(k,i)
c                  enddo
c                  do k=1,4
c                     print *,'(',i,') ','p6,pn2=',p6(k),pn2(k,i)
c                  enddo
                  
                  do k=1,3
                     val(k)=(p5(k)-pn1(k,i))/p5(k)
                     val(3+k)=(p6(k)-pn2(k,i))/p6(k)
                  enddo
                  
                  call stats(0,val,mean,rms,max,samp,6)
                  
               endif
            enddo
            class(5+sol)=class(5+sol)+1
         endif
      enddo

      call stats(1,val,mean,rms,max,samp,6)

      print *,' '
      print *,'**********************'
      do k=0,9
         print *,'class(',k,')=',class(k)
      enddo

      end

