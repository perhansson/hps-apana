c-------------------------------------------------------------
c Replacement for the PYTHIA random generator
c
      function pyr(dmy)
c-------------------------------------------------------------
      implicit none
      real*8 pyr
      real rnd(1)
      integer dmy
      call ranmar(rnd(1),1)
      pyr=dble(rnd(1))
      end

c-------------------------------------------------------------
c Init random generator
c
      subroutine inipyr(iseed)
c-------------------------------------------------------------
      implicit none
      integer iseed
      call rmarin(iseed,0,0)
      end
