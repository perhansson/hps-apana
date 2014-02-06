c------------------------------------------------------------------------
c
c 3C fit. tt->semi/hadron, t and W mass constraints + etmiss
c
c------------------------------------------------------------------------
      subroutine ttlh3c(pl1,pn1,pb1,pb2,pj1,pj2,metx,mety,rmb,rmw,rmt,
     |     rV,rchi2,yin,yout)
      implicit none
      include 'scale.inc'
      real*8 pl1(4),pj1(4),pb1(4),pb2(4),pj2(4),pn1(4)
      real*8 rmb,rmw,rmt,metx,mety,rV(Neta,Neta),rchi2
      real*8 y(Neta),xi(3),chi2,V(Neta,Neta),mb,mw,mt
      real*8 yin(Neta),yout(Neta)
      integer i,j
      real*8 enep,metz
      external enep,metz
      
      do i=1,Neta
         do j=1,Neta
            V(i,j)=rV(i,j)
         enddo
      enddo
      mb=rmb
      mw=rmw
      mt=rmt
      do i=1,3
         y(   i)=pl1(i)
         y( 3+i)=pj1(i)
         y( 6+i)=pb1(i)
         y( 9+i)=pb2(i)
         y(12+i)=pj2(i)
      enddo
      y(16)=mw
      y(17)=mw
      y(18)=mt
      y(19)=mt
      y(20)=metx
      y(21)=mety
      xi(1)=metx
      xi(2)=mety
      xi(3)=metz(y,xi,mb,mw,mt) ! neutrino z komponent from constraints

      do i=1,Neta
         yin(i)=y(i)
      enddo

      call genlsq(y,xi,V,chi2,mb)

      do i=1,3
         pl1(i)=y(   i)
         pj1(i)=y( 3+i)
         pb1(i)=y( 6+i)
         pb2(i)=y( 9+i)
         pj2(i)=y(12+i)
         pn1(i)=xi(i)
      enddo
      pl1(4)=enep(y(1),0d0)
      pj1(4)=enep(y(3),0d0)
      pb1(4)=enep(y(6),mb)
      pb2(4)=enep(y(9),mb)
      pj2(4)=enep(y(12),0d0)
      pn1(4)=enep(xi,0d0)
      rchi2=chi2
      
      do i=1,Neta
         yout(i)=y(i)
      enddo

      end

c------------------------------------------------------------------------
c
c General least square, Frodesen et. al. page 311.
c
c------------------------------------------------------------------------
      subroutine genlsq(y,xi,V,chi2,mb)
      implicit none
      include 'scale.inc'
      real*8 y(Neta),eta(Neta),xi(3),f(Nf),Fe(Nf,Neta),Fx(Nf,3)
      real*8 mb,V(Neta,Neta)
      real*8 eta_c(Neta),xi_c(3),l_c(Nf),chi2,chi2_c
      real*8 r(Nf),S(Nf,Nf),t4(Nf),t15(Neta),tm154(Neta,Nf),W(99)
      real*8 iS(Nf,Nf),d15(Neta),tm3(3,3),tm43(Nf,3),t3(3),m3(3,3)
      real*8 iV(Neta,Neta),itm3(3,3),det,fsum,A(3,3),B(3,Nf),iA(3,3)
      integer ifail,try,ir(Neta),jfail,i,j
      real*8 dvmpy
      real prob
      external dvmpy
      external prob

      try=0
      chi2=1d30
      call dvcpy(Neta,y(1),y(2),eta(1),eta(2))
      call dmcpy(Neta,Neta,V,V(1,2),V(2,1),iV,iV(1,2),iV(2,1))
      call dsinv(Neta,iV,Neta,ifail)
      if (ifail.ne.0) then
         print *,'inverse(V) failed, ifail=',ifail
         chi2=1d30
         return
      endif

c      print *,'start xi=',xi

 10   continue

      call f_set(f,eta,xi,mb)
      call Fe_set(Fe,eta,xi,mb)
      call Fx_set(Fx,eta,xi,mb)

c      print *,'f=',f
c      print *,'xi=',xi
c      print *,'Fe(1)=',(Fe(1,i),i=1,21)
c      print *,'Fe(2)=',(Fe(2,i),i=1,21)
c      print *,'Fe(3)=',(Fe(3,i),i=1,21)
c      print *,'Fe(4)=',(Fe(4,i),i=1,21)
c      print *,'Fe(5)=',(Fe(5,i),i=1,21)
c      print *,'Fe(6)=',(Fe(6,i),i=1,21)
c      print *,'Fx(1)=',(Fx(1,i),i=1,3)
c      print *,'Fx(2)=',(Fx(2,i),i=1,3)
c      print *,'Fx(3)=',(Fx(3,i),i=1,3)
c      print *,'Fx(4)=',(Fx(4,i),i=1,3)
c      print *,'Fx(5)=',(Fx(5,i),i=1,3)
c      print *,'Fx(6)=',(Fx(6,i),i=1,3)

c r=f+Fe*(y-eta)
      call dvsub(Neta,y(1),y(2),eta(1),eta(2),t15(1),t15(2))
      call dmmpy(Nf,Neta,Fe,Fe(1,2),Fe(2,1),t15(1),t15(2),t4(1),t4(2))
      call dvadd(Nf,f(1),f(2),t4(1),t4(2),r(1),r(2))

c S=Fe*(V*transpose(Fe))
      call dmmlt(Neta,Neta,Nf,V,V(1,2),V(2,1),Fe,Fe(2,1),Fe(1,2),
     |     tm154,tm154(1,2),tm154(2,1),W)
      call dmmlt(Nf,Neta,Nf,Fe,Fe(1,2),Fe(2,1),tm154,tm154(1,2),
     |     tm154(2,1),S,S(1,2),S(2,1),W)

c iS=inv(S)
      call dmcpy(Nf,Nf,S,S(1,2),S(2,1),iS,iS(1,2),iS(2,1))
      call dsfact(Nf,iS,Nf,ifail,det,jfail)
      if (ifail.ne.0) then
         print *,'inverse(S) failed, ifail=',ifail
         chi2=1d30
         return
      endif      
      if (jfail.ne.0) then
         print *,'inverse(S) failed, jfail=',jfail
         chi2=1d30
         return
      endif
      call dsfinv(Nf,iS,Nf)

c B=transpose(Fx)*iS
      call dmmlt(3,Nf,Nf,Fx,Fx(2,1),Fx(1,2),iS,iS(1,2),iS(2,1),
     |     B,B(1,2),B(2,1),W)

c      print *,'B(1)=',(B(1,i),i=1,Nf)
c      print *,'B(2)=',(B(2,i),i=1,Nf)
c      print *,'B(3)=',(B(3,i),i=1,Nf)

c A=B*Fx
      call dmmlt(3,Nf,3,B,B(1,2),B(2,1),Fx,Fx(1,2),Fx(2,1),
     |     A,A(1,2),A(2,1),W)

c      print *,'A(1)=',(A(1,i),i=1,3)
c      print *,'A(2)=',(A(2,i),i=1,3)
c      print *,'A(3)=',(A(3,i),i=1,3)

c iA=inv(A)
      call dmcpy(3,3,A,A(1,2),A(2,1),iA,iA(1,2),iA(2,1))
      call dsfact(3,iA,3,ifail,det,jfail)
      if (ifail.ne.0) then
         print *,'inv(A) failed, ifail=',ifail
         chi2=1e30
         return
      endif
      if (jfail.ne.0) then
         print *,'inv(A) failed, jfail=',jfail
         chi2=1e30
         return
      endif
      call dsfinv(3,iA,3)

c xi_c=xi-iA*B*r
      call dmmlt(3,3,Nf,iA,iA(1,2),iA(2,1),B,B(1,2),B(2,1),
     |     tm43,tm43(1,2),tm43(2,1),W)
      call dmmpy(3,3,tm43,tm43(1,2),tm43(2,1),r(1),r(2),t3(1),t3(2))
      call dvsub(3,xi(1),xi(2),t3(1),t3(2),xi_c(1),xi_c(2))
      
c l_c=inv(S)*(r+Fx*(xi_c-xi))
      call dvsub(3,xi_c(1),xi_c(2),xi(1),xi(2),t3(1),t3(2))
      call dmmpy(Nf,3,Fx,Fx(1,2),Fx(2,1),t3(1),t3(2),t4(1),t4(2))
      call dvadd(Nf,r(1),r(2),t4(1),t4(2),t4(1),t4(2))
      call dmmpy(Nf,Nf,iS,iS(1,2),iS(2,1),t4(1),t4(2),l_c(1),l_c(2))

c eta_c=y-V*transpose(Fe)*l_c
      call dmmpy(Neta,Nf,Fe,Fe(2,1),Fe(1,2),l_c(1),l_c(2),t15(1),t15(2))
      call dmmpy(Neta,Neta,V,V(1,2),V(2,1),t15(1),t15(2),t15(1),t15(2))
      call dvsub(Neta,y(1),y(2),t15(1),t15(2),eta_c(1),eta_c(2))

c chi2_c=transpose(y-eta_c)*inv(V)*(y-eta_c)+2*transpose(l_c)*f
      chi2_c=2d0*dvmpy(Nf,l_c(1),l_c(2),f(1),f(2))
      call dvsub(Neta,y(1),y(2),eta_c(1),eta_c(2),d15(1),d15(2))
      call dmmpy(Neta,Neta,iV,iV(1,2),iV(2,1),d15(1),d15(2),
     |     t15(1),t15(2))
      chi2_c=chi2_c+dvmpy(Neta,d15(1),d15(2),t15(1),t15(2))

      fsum=0d0
      do i=1,Nf
         fsum=fsum+abs(f(i))
      enddo

c      print *,'r=',r
c      print *,'xi_c=',xi_c
c      print *,'l_c=',l_c
c      print *,'iA(1)=',(A(1,i),i=1,3)
c      print *,'iA(2)=',(A(2,i),i=1,3)
c      print *,'iA(3)=',(A(3,i),i=1,3)
c      print *,'iS(1)=',(iS(1,i),i=1,6)
c      print *,'iS(2)=',(iS(2,i),i=1,6)
c      print *,'iS(3)=',(iS(3,i),i=1,6)
c      print *,'iS(4)=',(iS(4,i),i=1,6)
c      print *,'iS(5)=',(iS(5,i),i=1,6)
c      print *,'iS(6)=',(iS(6,i),i=1,6)

      if (abs(chi2-chi2_c).gt.0.5d0.or.fsum.gt.0.1) then
         try=try+1
         if (try.gt.30) then
c            print *,'Chi2 does not converge, try=',try
c            print *,'Chi2=',chi2_c
c            print *,'f=',f
c            print *,'xi=',xi
c            print *,'mass=',(eta(i),i=16,19)
            chi2=1d20
            goto 99
         endif
         call dvcpy(Neta,eta_c(1),eta_c(2),eta(1),eta(2))
         call dvcpy(3,xi_c(1),xi_c(2),xi(1),xi(2))
         chi2=chi2_c
         goto 10
      endif

      call dvcpy(Neta,eta_c(1),eta_c(2),y(1),y(2))
      call dvcpy(3,xi_c(1),xi_c(2),xi(1),xi(2))

c      if (prob(sngl(chi2_c),3).lt.0.01) then
c         print *,'Converged chi2=',chi2
c         print *,'f=',f
c         print *,'xi=',xi
c         print *,'try=',try
c         print *,'mass=',(eta(i),i=16,19)
c         print *,'t15=',t15
c         print *,'d15=',d15
c      endif

 99   continue

      end

c------------------------------------------------------------------------
      subroutine f_set(f,eta,xi,mb)
c------------------------------------------------------------------------
      implicit none
      include 'scale.inc'
      integer i
      real*8 f(Nf),eta(Neta),xi(3),mb
      real*8 p(4),enep
      external enep

      do i=1,3
         p(i)=eta(i)+xi(i)
      enddo
      p(4)=enep(eta(1),0d0)+enep(xi(1),0d0)
      f(1)=sc1*(p(4)**2-p(1)**2-p(2)**2-p(3)**2-eta(16)**2)
      do i=1,3
         p(i)=eta(3+i)+eta(12+i)
      enddo
      p(4)=enep(eta(4),0d0)+enep(eta(13),0d0)
      f(2)=sc2*(p(4)**2-p(1)**2-p(2)**2-p(3)**2-eta(17)**2)
      do i=1,3
         p(i)=eta(i)+xi(i)+eta(6+i)
      enddo
      p(4)=enep(eta(1),0d0)+enep(xi(1),0d0)+enep(eta(7),mb)
      f(3)=sc3*(p(4)**2-p(1)**2-p(2)**2-p(3)**2-eta(18)**2)
      do i=1,3
         p(i)=eta(3+i)+eta(12+i)+eta(9+i)
      enddo
      p(4)=enep(eta(4),0d0)+enep(eta(13),0d0)+enep(eta(10),mb)
      f(4)=sc4*(p(4)**2-p(1)**2-p(2)**2-p(3)**2-eta(19)**2)
      f(5)=sc5*(xi(1)-eta(Neta-1))
      f(6)=sc6*(xi(2)-eta(Neta))

      end

c------------------------------------------------------------------------
      subroutine Fe_set(Fe,eta,xi,mb)
c------------------------------------------------------------------------
      implicit none
      include 'scale.inc'
      real*8 Fe(Nf,Neta),eta(Neta),xi(3),mb
      real*8 Ee,Eu,Eb,Ebb,Ed,En
      integer i,j
      real*8 enep
      external enep

      Ee=enep(eta(1),0d0)
      Ed=enep(eta(4),0d0)
      Eb=enep(eta(7),mb)
      Ebb=enep(eta(10),mb)
      Eu=enep(eta(13),0d0)
      En=enep(xi(1),0d0)

      do i=1,Nf
         do j=1,Neta
            Fe(i,j)=0d0
         enddo
      enddo

      Fe(1,1)=sc1*2d0*(eta(1)*En/Ee-xi(1))
      Fe(1,2)=sc1*2d0*(eta(2)*En/Ee-xi(2))
      Fe(1,3)=sc1*2d0*(eta(3)*En/Ee-xi(3))
      Fe(1,16)=sc1*(-2d0*eta(16))

      Fe(2,4)=sc2*2d0*(eta(4)*Eu/Ed-eta(13))
      Fe(2,5)=sc2*2d0*(eta(5)*Eu/Ed-eta(14))
      Fe(2,6)=sc2*2d0*(eta(6)*Eu/Ed-eta(15))

      Fe(2,13)=sc2*2d0*(eta(13)*Ed/Eu-eta(4))
      Fe(2,14)=sc2*2d0*(eta(14)*Ed/Eu-eta(5))
      Fe(2,15)=sc2*2d0*(eta(15)*Ed/Eu-eta(6))

      Fe(2,17)=sc2*(-2d0*eta(17))

      Fe(3,1)=sc3*2d0*(eta(1)*(En+Eb)/Ee-xi(1)-eta(7))
      Fe(3,2)=sc3*2d0*(eta(2)*(En+Eb)/Ee-xi(2)-eta(8))
      Fe(3,3)=sc3*2d0*(eta(3)*(En+Eb)/Ee-xi(3)-eta(9))

      Fe(3,7)=sc3*2d0*(eta(7)*(En+Ee)/Eb-xi(1)-eta(1))
      Fe(3,8)=sc3*2d0*(eta(8)*(En+Ee)/Eb-xi(2)-eta(2))
      Fe(3,9)=sc3*2d0*(eta(9)*(En+Ee)/Eb-xi(3)-eta(3))

      Fe(3,18)=sc3*(-2d0*eta(18))

      Fe(4,4)=sc4*2d0*(eta(4)*(Eu+Ebb)/Ed-eta(13)-eta(10))
      Fe(4,5)=sc4*2d0*(eta(5)*(Eu+Ebb)/Ed-eta(14)-eta(11))
      Fe(4,6)=sc4*2d0*(eta(6)*(Eu+Ebb)/Ed-eta(15)-eta(12))

      Fe(4,10)=sc4*2d0*(eta(10)*(Eu+Ed)/Ebb-eta(13)-eta(4))
      Fe(4,11)=sc4*2d0*(eta(11)*(Eu+Ed)/Ebb-eta(14)-eta(5))
      Fe(4,12)=sc4*2d0*(eta(12)*(Eu+Ed)/Ebb-eta(15)-eta(6))

      Fe(4,13)=sc4*2d0*(eta(13)*(Ed+Ebb)/Eu-eta(4)-eta(10))
      Fe(4,14)=sc4*2d0*(eta(14)*(Ed+Ebb)/Eu-eta(5)-eta(11))
      Fe(4,15)=sc4*2d0*(eta(15)*(Ed+Ebb)/Eu-eta(6)-eta(12))

      Fe(4,19)=sc4*(-2d0*eta(19))

      Fe(5,20)=sc5*(-1d0)
      Fe(6,21)=sc6*(-1d0)

      end

c------------------------------------------------------------------------
      subroutine Fx_set(Fx,eta,xi,mb)
c------------------------------------------------------------------------
      implicit none
      include 'scale.inc'
      real*8 Fx(Nf,3),eta(Neta),xi(3),mb
      real*8 Ee,Eb,En
      integer i,j
      real*8 enep
      external enep      

      Ee=enep(eta(1),0d0)
      Eb=enep(eta(7),mb)
      En=enep(xi(1),0d0)

      do i=1,Nf
         do j=1,3
            Fx(i,j)=0d0
         enddo
      enddo

      Fx(1,1)=sc1*2d0*(xi(1)*Ee/En-eta(1))
      Fx(1,2)=sc1*2d0*(xi(2)*Ee/En-eta(2))
      Fx(1,3)=sc1*2d0*(xi(3)*Ee/En-eta(3))

      Fx(3,1)=sc3*2d0*(xi(1)*(Ee+Eb)/En-eta(1)-eta(7))
      Fx(3,2)=sc3*2d0*(xi(2)*(Ee+Eb)/En-eta(2)-eta(8))
      Fx(3,3)=sc3*2d0*(xi(3)*(Ee+Eb)/En-eta(3)-eta(9))

      Fx(5,1)=sc5*(1d0)
      Fx(6,2)=sc6*(1d0)

      end


c------------------------------------------------------------------------
      real*8 function metz(y,xi,mb,mw,mt)
c------------------------------------------------------------------------
      implicit none
      include 'scale.inc'
      real*8 y(Neta),xi(3)
      real*8 Ee,Eb,pkx,pky,pkz,peb,c,mb,mw,mt
      real*8 enep
      external enep
      
      Ee=enep(y(1),0d0)
      Eb=enep(y(7),mb)
      pkx=((Ee+Eb)/Ee)*y(1)-y(1)-y(7)
      pky=((Ee+Eb)/Ee)*y(2)-y(2)-y(8)
      pkz=((Ee+Eb)/Ee)*y(3)-y(3)-y(9)
      peb=y(1)*y(7)+y(2)*y(8)+y(3)*y(9)
      c=((Ee+Eb)/Ee)*(mw**2)/2d0+Ee*Eb+(mb**2-mt**2)/2d0-peb
      metz=(-c-pkx*xi(1)-pky*xi(2))/pkz
      
      end

c------------------------------------------------------------------------
      real*8 function enep(p,m)
c------------------------------------------------------------------------
      implicit none
      real*8 p(3),m

      enep=sqrt(p(1)**2+p(2)**2+p(3)**2+m**2)

      end




