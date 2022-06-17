
/*
 * This code was generated by Spiral 8.4.0-release, www.spiral.net
 */

#include "../omega64.h"
#include <stdint.h>
static float D1[64];
static float D2[1024];

extern "C" {
void init_fftx_dftbat_1_512_1d_CPU()
{
  for (int i7 = 0; i7 <= 7; i7++) {
    for (int i18 = 0; i18 <= 1; i18++) {
      D1[((8 * i7) + (4 * i18))]     = cospi((((float)(62 * (i7 * i18))) / 32));
      D1[(1 + (8 * i7) + (4 * i18))] = sinpi((((float)(62 * (i7 * i18))) / 32));
      D1[(2 + (8 * i7) + (4 * i18))] = cospi((((float)(62 * (i7 * (2 + i18)))) / 32));
      D1[(3 + (8 * i7) + (4 * i18))] = sinpi((((float)(62 * (i7 * (2 + i18)))) / 32));
    }
  }
  for (int i3 = 0; i3 <= 31; i3++) {
    for (int i10 = 0; i10 <= 3; i10++) {
      for (int i22 = 0; i22 <= 1; i22++) {
        D2[((32 * i3) + (8 * i10) + (4 * i22))]     = cospi((((float)(1022 * (i3 * ((4 * i22) + i10)))) / 512));
        D2[(1 + (32 * i3) + (8 * i10) + (4 * i22))] = sinpi((((float)(1022 * (i3 * ((4 * i22) + i10)))) / 512));
        D2[(2 + (32 * i3) + (8 * i10) + (4 * i22))] = cospi((((float)(1022 * (i3 * (8 + (4 * i22) + i10)))) / 512));
        D2[(3 + (32 * i3) + (8 * i10) + (4 * i22))] = sinpi((((float)(1022 * (i3 * (8 + (4 * i22) + i10)))) / 512));
      }
    }
  }
}
}

extern "C" {
void fftx_dftbat_1_512_1d_CPU(float* Y, float* X)
{
  static float T1[1024];
  for (int i3 = 0; i3 <= 31; i3++) {
    float a654, a655, a664, a665, a666, a667, a676, a677, s145, s146, s147, s148, s149, s150, s151, s152, s153, s154,
        s155, s156, s157, s158, s159, s160, t450, t451, t452, t453, t454, t455, t456, t457, t458, t459, t460, t461,
        t462, t463, t464, t465, t466, t467, t468, t469, t470, t471, t472, t473, t474, t475, t476, t477, t478, t479,
        t480, t481, t482, t483, t484, t485, t486, t487, t488, t489, t490, t491, t492, t493, t494, t495, t496, t497,
        t498, t499, t500, t501, t502, t503, t504, t505, t506, t507, t508, t509, t510, t511, t512, t513, t514, t515,
        t516, t517, t518, t519, t520, t521, t522, t523, t524, t525, t526, t527, t528, t529, t530, t531, t532, t533,
        t534, t535, t536, t537, t538, t539, t540, t541, t542, t543, t544, t545, t546, t547, t548, t549, t550, t551,
        t552, t553, t554, t555, t556, t557, t558, t559, t560, t561, t562, t563, t564, t565, t566, t567, t568, t569;
    int a638, a639, a640, a641, a642, a643, a644, a645, a646, a647, a648, a649, a650, a651, a652, a653, a656, a657,
        a658, a659, a660, a661, a662, a663, a668, a669, a670, a671, a672, a673, a674, a675, a678, a679, a680, a681,
        a682, a683, a684, a685, a686, a687, a688, a689, a690, a691, a692, a693, a694, a695, a696, a697, a698, a699,
        a700, a701, a702, a703, a704, a705, a706, a707, a708, a709;
    a638           = (2 * i3);
    a639           = (a638 + 1);
    a640           = (a638 + 512);
    a641           = (a638 + 513);
    t450           = (*((X + a638)) + *((X + a640)));
    t451           = (*((X + a639)) + *((X + a641)));
    t452           = (*((X + a638)) - *((X + a640)));
    t453           = (*((X + a639)) - *((X + a641)));
    a642           = (a638 + 256);
    a643           = (a638 + 257);
    a644           = (a638 + 768);
    a645           = (a638 + 769);
    t454           = (*((X + a642)) + *((X + a644)));
    t455           = (*((X + a643)) + *((X + a645)));
    t456           = (*((X + a642)) - *((X + a644)));
    t457           = (*((X + a643)) - *((X + a645)));
    t458           = (t450 + t454);
    t459           = (t451 + t455);
    t460           = (t450 - t454);
    t461           = (t451 - t455);
    t462           = (t452 + t457);
    t463           = (t453 - t456);
    t464           = (t452 - t457);
    t465           = (t453 + t456);
    a646           = (a638 + 64);
    a647           = (a638 + 65);
    a648           = (a638 + 576);
    a649           = (a638 + 577);
    t466           = (*((X + a646)) + *((X + a648)));
    t467           = (*((X + a647)) + *((X + a649)));
    t468           = (*((X + a646)) - *((X + a648)));
    t469           = (*((X + a647)) - *((X + a649)));
    a650           = (a638 + 320);
    a651           = (a638 + 321);
    a652           = (a638 + 832);
    a653           = (a638 + 833);
    t470           = (*((X + a650)) + *((X + a652)));
    t471           = (*((X + a651)) + *((X + a653)));
    t472           = (*((X + a650)) - *((X + a652)));
    t473           = (*((X + a651)) - *((X + a653)));
    t474           = (t466 + t470);
    t475           = (t467 + t471);
    a654           = (0.70710678118654757 * (t466 - t470));
    a655           = (0.70710678118654757 * (t467 - t471));
    s145           = (a654 + a655);
    s146           = (a655 - a654);
    t476           = (t468 + t473);
    t477           = (t469 - t472);
    t478           = (t468 - t473);
    t479           = (t469 + t472);
    s147           = ((0.92387953251128674 * t476) + (0.38268343236508978 * t477));
    s148           = ((0.92387953251128674 * t477) - (0.38268343236508978 * t476));
    s149           = ((0.38268343236508978 * t478) + (0.92387953251128674 * t479));
    s150           = ((0.38268343236508978 * t479) - (0.92387953251128674 * t478));
    a656           = (a638 + 128);
    a657           = (a638 + 129);
    a658           = (a638 + 640);
    a659           = (a638 + 641);
    t480           = (*((X + a656)) + *((X + a658)));
    t481           = (*((X + a657)) + *((X + a659)));
    t482           = (*((X + a656)) - *((X + a658)));
    t483           = (*((X + a657)) - *((X + a659)));
    a660           = (a638 + 384);
    a661           = (a638 + 385);
    a662           = (a638 + 896);
    a663           = (a638 + 897);
    t484           = (*((X + a660)) + *((X + a662)));
    t485           = (*((X + a661)) + *((X + a663)));
    t486           = (*((X + a660)) - *((X + a662)));
    t487           = (*((X + a661)) - *((X + a663)));
    t488           = (t480 + t484);
    t489           = (t481 + t485);
    t490           = (t480 - t484);
    t491           = (t481 - t485);
    a664           = (0.70710678118654757 * (t482 + t487));
    a665           = (0.70710678118654757 * (t483 - t486));
    s151           = (a664 + a665);
    s152           = (a665 - a664);
    a666           = (0.70710678118654757 * (t483 + t486));
    a667           = (0.70710678118654757 * (t482 - t487));
    s153           = (a666 - a667);
    s154           = (a667 + a666);
    a668           = (a638 + 192);
    a669           = (a638 + 193);
    a670           = (a638 + 704);
    a671           = (a638 + 705);
    t492           = (*((X + a668)) + *((X + a670)));
    t493           = (*((X + a669)) + *((X + a671)));
    t494           = (*((X + a668)) - *((X + a670)));
    t495           = (*((X + a669)) - *((X + a671)));
    a672           = (a638 + 448);
    a673           = (a638 + 449);
    a674           = (a638 + 960);
    a675           = (a638 + 961);
    t496           = (*((X + a672)) + *((X + a674)));
    t497           = (*((X + a673)) + *((X + a675)));
    t498           = (*((X + a672)) - *((X + a674)));
    t499           = (*((X + a673)) - *((X + a675)));
    t500           = (t492 + t496);
    t501           = (t493 + t497);
    a676           = (0.70710678118654757 * (t493 - t497));
    a677           = (0.70710678118654757 * (t492 - t496));
    s155           = (a676 - a677);
    s156           = (a677 + a676);
    t502           = (t494 + t499);
    t503           = (t495 - t498);
    t504           = (t494 - t499);
    t505           = (t495 + t498);
    s157           = ((0.38268343236508978 * t502) + (0.92387953251128674 * t503));
    s158           = ((0.38268343236508978 * t503) - (0.92387953251128674 * t502));
    s159           = ((0.92387953251128674 * t504) + (0.38268343236508978 * t505));
    s160           = ((0.38268343236508978 * t504) - (0.92387953251128674 * t505));
    t506           = (t458 + t488);
    t507           = (t459 + t489);
    t508           = (t458 - t488);
    t509           = (t459 - t489);
    t510           = (t474 + t500);
    t511           = (t475 + t501);
    t512           = (t474 - t500);
    t513           = (t475 - t501);
    t514           = (t506 + t510);
    t515           = (t507 + t511);
    t516           = (t506 - t510);
    t517           = (t507 - t511);
    a678           = (32 * i3);
    a679           = (a678 + 1);
    a680           = (a678 + 2);
    a681           = (a678 + 3);
    *((T1 + a678)) = ((*((D2 + a678)) * t514) - (*((D2 + a679)) * t515));
    *((T1 + a679)) = ((*((D2 + a679)) * t514) + (*((D2 + a678)) * t515));
    a682           = (a678 + 16);
    *((T1 + a682)) = ((*((D2 + a680)) * t516) - (*((D2 + a681)) * t517));
    a683           = (a678 + 17);
    *((T1 + a683)) = ((*((D2 + a681)) * t516) + (*((D2 + a680)) * t517));
    t518           = (t508 + t513);
    t519           = (t509 - t512);
    t520           = (t508 - t513);
    t521           = (t509 + t512);
    a684           = (a678 + 4);
    a685           = (a678 + 5);
    a686           = (a678 + 6);
    a687           = (a678 + 7);
    a688           = (a678 + 8);
    *((T1 + a688)) = ((*((D2 + a684)) * t518) - (*((D2 + a685)) * t519));
    a689           = (a678 + 9);
    *((T1 + a689)) = ((*((D2 + a685)) * t518) + (*((D2 + a684)) * t519));
    a690           = (a678 + 24);
    *((T1 + a690)) = ((*((D2 + a686)) * t520) - (*((D2 + a687)) * t521));
    a691           = (a678 + 25);
    *((T1 + a691)) = ((*((D2 + a687)) * t520) + (*((D2 + a686)) * t521));
    t522           = (t462 + s151);
    t523           = (t463 + s152);
    t524           = (t462 - s151);
    t525           = (t463 - s152);
    t526           = (s147 + s157);
    t527           = (s148 + s158);
    t528           = (s147 - s157);
    t529           = (s148 - s158);
    t530           = (t522 + t526);
    t531           = (t523 + t527);
    t532           = (t522 - t526);
    t533           = (t523 - t527);
    a692           = (a678 + 10);
    a693           = (a678 + 11);
    *((T1 + a680)) = ((*((D2 + a688)) * t530) - (*((D2 + a689)) * t531));
    *((T1 + a681)) = ((*((D2 + a689)) * t530) + (*((D2 + a688)) * t531));
    a694           = (a678 + 18);
    *((T1 + a694)) = ((*((D2 + a692)) * t532) - (*((D2 + a693)) * t533));
    a695           = (a678 + 19);
    *((T1 + a695)) = ((*((D2 + a693)) * t532) + (*((D2 + a692)) * t533));
    t534           = (t524 + t529);
    t535           = (t525 - t528);
    t536           = (t524 - t529);
    t537           = (t525 + t528);
    a696           = (a678 + 12);
    a697           = (a678 + 13);
    a698           = (a678 + 14);
    a699           = (a678 + 15);
    *((T1 + a692)) = ((*((D2 + a696)) * t534) - (*((D2 + a697)) * t535));
    *((T1 + a693)) = ((*((D2 + a697)) * t534) + (*((D2 + a696)) * t535));
    a700           = (a678 + 26);
    *((T1 + a700)) = ((*((D2 + a698)) * t536) - (*((D2 + a699)) * t537));
    a701           = (a678 + 27);
    *((T1 + a701)) = ((*((D2 + a699)) * t536) + (*((D2 + a698)) * t537));
    t538           = (t460 + t491);
    t539           = (t461 - t490);
    t540           = (t460 - t491);
    t541           = (t461 + t490);
    t542           = (s145 + s155);
    t543           = (s146 - s156);
    t544           = (s145 - s155);
    t545           = (s146 + s156);
    t546           = (t538 + t542);
    t547           = (t539 + t543);
    t548           = (t538 - t542);
    t549           = (t539 - t543);
    *((T1 + a684)) = ((*((D2 + a682)) * t546) - (*((D2 + a683)) * t547));
    *((T1 + a685)) = ((*((D2 + a683)) * t546) + (*((D2 + a682)) * t547));
    a702           = (a678 + 20);
    *((T1 + a702)) = ((*((D2 + a694)) * t548) - (*((D2 + a695)) * t549));
    a703           = (a678 + 21);
    *((T1 + a703)) = ((*((D2 + a695)) * t548) + (*((D2 + a694)) * t549));
    t550           = (t540 + t545);
    t551           = (t541 - t544);
    t552           = (t540 - t545);
    t553           = (t541 + t544);
    a704           = (a678 + 22);
    a705           = (a678 + 23);
    *((T1 + a696)) = ((*((D2 + a702)) * t550) - (*((D2 + a703)) * t551));
    *((T1 + a697)) = ((*((D2 + a703)) * t550) + (*((D2 + a702)) * t551));
    a706           = (a678 + 28);
    *((T1 + a706)) = ((*((D2 + a704)) * t552) - (*((D2 + a705)) * t553));
    a707           = (a678 + 29);
    *((T1 + a707)) = ((*((D2 + a705)) * t552) + (*((D2 + a704)) * t553));
    t554           = (t464 + s153);
    t555           = (t465 - s154);
    t556           = (t464 - s153);
    t557           = (t465 + s154);
    t558           = (s149 - s159);
    t559           = (s150 + s160);
    t560           = (s149 + s159);
    t561           = (s150 - s160);
    t562           = (t554 + t558);
    t563           = (t555 + t559);
    t564           = (t554 - t558);
    t565           = (t555 - t559);
    *((T1 + a686)) = ((*((D2 + a690)) * t562) - (*((D2 + a691)) * t563));
    *((T1 + a687)) = ((*((D2 + a691)) * t562) + (*((D2 + a690)) * t563));
    *((T1 + a704)) = ((*((D2 + a700)) * t564) - (*((D2 + a701)) * t565));
    *((T1 + a705)) = ((*((D2 + a701)) * t564) + (*((D2 + a700)) * t565));
    t566           = (t556 + t561);
    t567           = (t557 - t560);
    t568           = (t556 - t561);
    t569           = (t557 + t560);
    a708           = (a678 + 30);
    a709           = (a678 + 31);
    *((T1 + a698)) = ((*((D2 + a706)) * t566) - (*((D2 + a707)) * t567));
    *((T1 + a699)) = ((*((D2 + a707)) * t566) + (*((D2 + a706)) * t567));
    *((T1 + a708)) = ((*((D2 + a708)) * t568) - (*((D2 + a709)) * t569));
    *((T1 + a709)) = ((*((D2 + a709)) * t568) + (*((D2 + a708)) * t569));
  }
  for (int i2 = 0; i2 <= 15; i2++) {
    static float T17[64];
    for (int i7 = 0; i7 <= 7; i7++) {
      float t618, t619, t620, t621, t622, t623, t624, t625, t626, t627, t628, t629, t630, t631, t632, t633;
      int   a861, a862, a863, a864, a865, a866, a867, a868, a869, a870, a871, a872, a873, a874, a875, a876;
      a861            = ((2 * i2) + (32 * i7));
      a862            = (a861 + 1);
      a863            = (a861 + 512);
      a864            = (a861 + 513);
      t618            = (*((T1 + a861)) + *((T1 + a863)));
      t619            = (*((T1 + a862)) + *((T1 + a864)));
      t620            = (*((T1 + a861)) - *((T1 + a863)));
      t621            = (*((T1 + a862)) - *((T1 + a864)));
      a865            = (a861 + 256);
      a866            = (a861 + 257);
      a867            = (a861 + 768);
      a868            = (a861 + 769);
      t622            = (*((T1 + a865)) + *((T1 + a867)));
      t623            = (*((T1 + a866)) + *((T1 + a868)));
      t624            = (*((T1 + a865)) - *((T1 + a867)));
      t625            = (*((T1 + a866)) - *((T1 + a868)));
      t626            = (t618 + t622);
      t627            = (t619 + t623);
      t628            = (t618 - t622);
      t629            = (t619 - t623);
      a869            = (8 * i7);
      a870            = (a869 + 1);
      a871            = (a869 + 2);
      a872            = (a869 + 3);
      *((T17 + a869)) = ((*((D1 + a869)) * t626) - (*((D1 + a870)) * t627));
      *((T17 + a870)) = ((*((D1 + a870)) * t626) + (*((D1 + a869)) * t627));
      a873            = (a869 + 4);
      *((T17 + a873)) = ((*((D1 + a871)) * t628) - (*((D1 + a872)) * t629));
      a874            = (a869 + 5);
      *((T17 + a874)) = ((*((D1 + a872)) * t628) + (*((D1 + a871)) * t629));
      t630            = (t620 + t625);
      t631            = (t621 - t624);
      t632            = (t620 - t625);
      t633            = (t621 + t624);
      a875            = (a869 + 6);
      a876            = (a869 + 7);
      *((T17 + a871)) = ((*((D1 + a873)) * t630) - (*((D1 + a874)) * t631));
      *((T17 + a872)) = ((*((D1 + a874)) * t630) + (*((D1 + a873)) * t631));
      *((T17 + a875)) = ((*((D1 + a875)) * t632) - (*((D1 + a876)) * t633));
      *((T17 + a876)) = ((*((D1 + a876)) * t632) + (*((D1 + a875)) * t633));
    }
    for (int i6 = 0; i6 <= 3; i6++) {
      float a1031, a1032, a1041, a1042, s213, s214, s215, s216, t758, t759, t760, t761, t762, t763, t764, t765, t766,
          t767, t768, t769, t770, t771, t772, t773, t774, t775, t776, t777, t778, t779, t780, t781, t782, t783, t784,
          t785;
      int a1023, a1024, a1025, a1026, a1027, a1028, a1029, a1030, a1033, a1034, a1035, a1036, a1037, a1038, a1039,
          a1040, a1043;
      a1023                = (2 * i6);
      a1024                = (a1023 + 1);
      a1025                = (a1023 + 32);
      a1026                = (a1023 + 33);
      t758                 = (*((T17 + a1023)) + *((T17 + a1025)));
      t759                 = (*((T17 + a1024)) + *((T17 + a1026)));
      t760                 = (*((T17 + a1023)) - *((T17 + a1025)));
      t761                 = (*((T17 + a1024)) - *((T17 + a1026)));
      a1027                = (a1023 + 8);
      a1028                = (a1023 + 9);
      a1029                = (a1023 + 40);
      a1030                = (a1023 + 41);
      t762                 = (*((T17 + a1027)) + *((T17 + a1029)));
      t763                 = (*((T17 + a1028)) + *((T17 + a1030)));
      a1031                = (0.70710678118654757 * (*((T17 + a1027)) - *((T17 + a1029))));
      a1032                = (0.70710678118654757 * (*((T17 + a1028)) - *((T17 + a1030))));
      s213                 = (a1031 + a1032);
      s214                 = (a1032 - a1031);
      a1033                = (a1023 + 16);
      a1034                = (a1023 + 17);
      a1035                = (a1023 + 48);
      a1036                = (a1023 + 49);
      t764                 = (*((T17 + a1033)) + *((T17 + a1035)));
      t765                 = (*((T17 + a1034)) + *((T17 + a1036)));
      t766                 = (*((T17 + a1033)) - *((T17 + a1035)));
      t767                 = (*((T17 + a1034)) - *((T17 + a1036)));
      a1037                = (a1023 + 24);
      a1038                = (a1023 + 25);
      a1039                = (a1023 + 56);
      a1040                = (a1023 + 57);
      t768                 = (*((T17 + a1037)) + *((T17 + a1039)));
      t769                 = (*((T17 + a1038)) + *((T17 + a1040)));
      a1041                = (0.70710678118654757 * (*((T17 + a1038)) - *((T17 + a1040))));
      a1042                = (0.70710678118654757 * (*((T17 + a1037)) - *((T17 + a1039))));
      s215                 = (a1041 - a1042);
      s216                 = (a1042 + a1041);
      t770                 = (t758 + t764);
      t771                 = (t759 + t765);
      t772                 = (t758 - t764);
      t773                 = (t759 - t765);
      t774                 = (t762 + t768);
      t775                 = (t763 + t769);
      t776                 = (t762 - t768);
      t777                 = (t763 - t769);
      a1043                = ((2 * i2) + (32 * i6));
      *((Y + a1043))       = (t770 + t774);
      *((1 + Y + a1043))   = (t771 + t775);
      *((512 + Y + a1043)) = (t770 - t774);
      *((513 + Y + a1043)) = (t771 - t775);
      *((256 + Y + a1043)) = (t772 + t777);
      *((257 + Y + a1043)) = (t773 - t776);
      *((768 + Y + a1043)) = (t772 - t777);
      *((769 + Y + a1043)) = (t773 + t776);
      t778                 = (t760 + t767);
      t779                 = (t761 - t766);
      t780                 = (t760 - t767);
      t781                 = (t761 + t766);
      t782                 = (s213 + s215);
      t783                 = (s214 - s216);
      t784                 = (s213 - s215);
      t785                 = (s214 + s216);
      *((128 + Y + a1043)) = (t778 + t782);
      *((129 + Y + a1043)) = (t779 + t783);
      *((640 + Y + a1043)) = (t778 - t782);
      *((641 + Y + a1043)) = (t779 - t783);
      *((384 + Y + a1043)) = (t780 + t785);
      *((385 + Y + a1043)) = (t781 - t784);
      *((896 + Y + a1043)) = (t780 - t785);
      *((897 + Y + a1043)) = (t781 + t784);
    }
  }
}
}

extern "C" {
void destroy_fftx_dftbat_1_512_1d_CPU()
{
  /* skip */
}
}
