
/*
 * This code was generated by Spiral 8.4.0-release, www.spiral.net
 */

#include "../omega64.h"
#include <stdint.h>
static float D1[128];
static float D2[4096];
static float D3[64];

extern "C" {
void init_fftx_dftbat_1_2048_1d_CPU()
{
  for (int i7 = 0; i7 <= 7; i7++) {
    for (int i18 = 0; i18 <= 1; i18++) {
      for (int i34 = 0; i34 <= 1; i34++) {
        D1[((16 * i7) + (8 * i18) + (4 * i34))]     = cospi((((float)(126 * (i7 * ((2 * i34) + i18)))) / 64));
        D1[(1 + (16 * i7) + (8 * i18) + (4 * i34))] = sinpi((((float)(126 * (i7 * ((2 * i34) + i18)))) / 64));
        D1[(2 + (16 * i7) + (8 * i18) + (4 * i34))] = cospi((((float)(126 * (i7 * (4 + (2 * i34) + i18)))) / 64));
        D1[(3 + (16 * i7) + (8 * i18) + (4 * i34))] = sinpi((((float)(126 * (i7 * (4 + (2 * i34) + i18)))) / 64));
      }
    }
  }
  for (int i3 = 0; i3 <= 63; i3++) {
    for (int i10 = 0; i10 <= 3; i10++) {
      for (int i22 = 0; i22 <= 1; i22++) {
        for (int i38 = 0; i38 <= 1; i38++) {
          D2[((64 * i3) + (16 * i10) + (8 * i22) + (4 * i38))] =
              cospi((((float)(4094 * (i3 * ((8 * i38) + (4 * i22) + i10)))) / 2048));
          D2[(1 + (64 * i3) + (16 * i10) + (8 * i22) + (4 * i38))] =
              sinpi((((float)(4094 * (i3 * ((8 * i38) + (4 * i22) + i10)))) / 2048));
          D2[(2 + (64 * i3) + (16 * i10) + (8 * i22) + (4 * i38))] =
              cospi((((float)(4094 * (i3 * (16 + (8 * i38) + (4 * i22) + i10)))) / 2048));
          D2[(3 + (64 * i3) + (16 * i10) + (8 * i22) + (4 * i38))] =
              sinpi((((float)(4094 * (i3 * (16 + (8 * i38) + (4 * i22) + i10)))) / 2048));
        }
      }
    }
  }
  for (int i11 = 0; i11 <= 7; i11++) {
    for (int i26 = 0; i26 <= 1; i26++) {
      D3[((8 * i11) + (4 * i26))]     = cospi((((float)(62 * (i11 * i26))) / 32));
      D3[(1 + (8 * i11) + (4 * i26))] = sinpi((((float)(62 * (i11 * i26))) / 32));
      D3[(2 + (8 * i11) + (4 * i26))] = cospi((((float)(62 * (i11 * (2 + i26)))) / 32));
      D3[(3 + (8 * i11) + (4 * i26))] = sinpi((((float)(62 * (i11 * (2 + i26)))) / 32));
    }
  }
}
}

extern "C" {
void fftx_dftbat_1_2048_1d_CPU(float* Y, float* X)
{
  static float T1[4096];
  for (int i3 = 0; i3 <= 63; i3++) {
    static float T2[64];
    for (int i11 = 0; i11 <= 7; i11++) {
      float t137, t138, t139, t140, t141, t142, t143, t144, t145, t146, t147, t148, t149, t150, t151, t152;
      int   a154, a155, a156, a157, a158, a159, a160, a161, a162, a163, a164, a165, a166, a167, a168, a169, a170, a171,
          b10;
      a154           = (128 * i11);
      a155           = (2 * i3);
      a156           = (a154 + a155);
      b10            = (a155 + a154);
      a157           = (b10 + 1);
      a158           = (b10 + 2048);
      a159           = (b10 + 2049);
      t137           = (*((X + a156)) + *((X + a158)));
      t138           = (*((X + a157)) + *((X + a159)));
      t139           = (*((X + a156)) - *((X + a158)));
      t140           = (*((X + a157)) - *((X + a159)));
      a160           = (b10 + 1024);
      a161           = (b10 + 1025);
      a162           = (b10 + 3072);
      a163           = (b10 + 3073);
      t141           = (*((X + a160)) + *((X + a162)));
      t142           = (*((X + a161)) + *((X + a163)));
      t143           = (*((X + a160)) - *((X + a162)));
      t144           = (*((X + a161)) - *((X + a163)));
      t145           = (t137 + t141);
      t146           = (t138 + t142);
      t147           = (t137 - t141);
      t148           = (t138 - t142);
      a164           = (8 * i11);
      a165           = (a164 + 1);
      a166           = (a164 + 2);
      a167           = (a164 + 3);
      *((T2 + a164)) = ((*((D3 + a164)) * t145) - (*((D3 + a165)) * t146));
      *((T2 + a165)) = ((*((D3 + a165)) * t145) + (*((D3 + a164)) * t146));
      a168           = (a164 + 4);
      *((T2 + a168)) = ((*((D3 + a166)) * t147) - (*((D3 + a167)) * t148));
      a169           = (a164 + 5);
      *((T2 + a169)) = ((*((D3 + a167)) * t147) + (*((D3 + a166)) * t148));
      t149           = (t139 + t144);
      t150           = (t140 - t143);
      t151           = (t139 - t144);
      t152           = (t140 + t143);
      a170           = (a164 + 6);
      a171           = (a164 + 7);
      *((T2 + a166)) = ((*((D3 + a168)) * t149) - (*((D3 + a169)) * t150));
      *((T2 + a167)) = ((*((D3 + a169)) * t149) + (*((D3 + a168)) * t150));
      *((T2 + a170)) = ((*((D3 + a170)) * t151) - (*((D3 + a171)) * t152));
      *((T2 + a171)) = ((*((D3 + a171)) * t151) + (*((D3 + a170)) * t152));
    }
    for (int i10 = 0; i10 <= 3; i10++) {
      float a552, a553, a562, a563, s85, s86, s87, s88, t293, t294, t295, t296, t297, t298, t299, t300, t301, t302,
          t303, t304, t305, t306, t307, t308, t309, t310, t311, t312, t313, t314, t315, t316, t317, t318, t319, t320,
          t321, t322, t323, t324, t325, t326, t327, t328, t329, t330, t331, t332, t333, t334, t335, t336;
      int a544, a545, a546, a547, a548, a549, a550, a551, a554, a555, a556, a557, a558, a559, a560, a561, a564, a565,
          a566, a567, a568, a569, a570, a571, a572, a573, a574, a575, a576, a577, a578, a579, a580, a581, b60, b61;
      a544                  = (2 * i10);
      a545                  = (a544 + 1);
      a546                  = (a544 + 32);
      a547                  = (a544 + 33);
      t293                  = (*((T2 + a544)) + *((T2 + a546)));
      t294                  = (*((T2 + a545)) + *((T2 + a547)));
      t295                  = (*((T2 + a544)) - *((T2 + a546)));
      t296                  = (*((T2 + a545)) - *((T2 + a547)));
      a548                  = (a544 + 8);
      a549                  = (a544 + 9);
      a550                  = (a544 + 40);
      a551                  = (a544 + 41);
      t297                  = (*((T2 + a548)) + *((T2 + a550)));
      t298                  = (*((T2 + a549)) + *((T2 + a551)));
      a552                  = (0.70710678118654757 * (*((T2 + a548)) - *((T2 + a550))));
      a553                  = (0.70710678118654757 * (*((T2 + a549)) - *((T2 + a551))));
      s85                   = (a552 + a553);
      s86                   = (a553 - a552);
      a554                  = (a544 + 16);
      a555                  = (a544 + 17);
      a556                  = (a544 + 48);
      a557                  = (a544 + 49);
      t299                  = (*((T2 + a554)) + *((T2 + a556)));
      t300                  = (*((T2 + a555)) + *((T2 + a557)));
      t301                  = (*((T2 + a554)) - *((T2 + a556)));
      t302                  = (*((T2 + a555)) - *((T2 + a557)));
      a558                  = (a544 + 24);
      a559                  = (a544 + 25);
      a560                  = (a544 + 56);
      a561                  = (a544 + 57);
      t303                  = (*((T2 + a558)) + *((T2 + a560)));
      t304                  = (*((T2 + a559)) + *((T2 + a561)));
      a562                  = (0.70710678118654757 * (*((T2 + a559)) - *((T2 + a561))));
      a563                  = (0.70710678118654757 * (*((T2 + a558)) - *((T2 + a560))));
      s87                   = (a562 - a563);
      s88                   = (a563 + a562);
      t305                  = (t293 + t299);
      t306                  = (t294 + t300);
      t307                  = (t293 - t299);
      t308                  = (t294 - t300);
      t309                  = (t297 + t303);
      t310                  = (t298 + t304);
      t311                  = (t297 - t303);
      t312                  = (t298 - t304);
      t313                  = (t305 + t309);
      t314                  = (t306 + t310);
      t315                  = (t305 - t309);
      t316                  = (t306 - t310);
      a564                  = (16 * i10);
      a565                  = (64 * i3);
      a566                  = (a564 + a565);
      b60                   = (a565 + a564);
      a567                  = (b60 + 1);
      a568                  = (b60 + 2);
      a569                  = (b60 + 3);
      *((T1 + a544 + a565)) = ((*((D2 + a566)) * t313) - (*((D2 + a567)) * t314));
      b61                   = (a565 + a544);
      *((1 + T1 + b61))     = ((*((D2 + a567)) * t313) + (*((D2 + a566)) * t314));
      *((32 + T1 + b61))    = ((*((D2 + a568)) * t315) - (*((D2 + a569)) * t316));
      *((33 + T1 + b61))    = ((*((D2 + a569)) * t315) + (*((D2 + a568)) * t316));
      t317                  = (t307 + t312);
      t318                  = (t308 - t311);
      t319                  = (t307 - t312);
      t320                  = (t308 + t311);
      a570                  = (b60 + 4);
      a571                  = (b60 + 5);
      a572                  = (b60 + 6);
      a573                  = (b60 + 7);
      *((16 + T1 + b61))    = ((*((D2 + a570)) * t317) - (*((D2 + a571)) * t318));
      *((17 + T1 + b61))    = ((*((D2 + a571)) * t317) + (*((D2 + a570)) * t318));
      *((48 + T1 + b61))    = ((*((D2 + a572)) * t319) - (*((D2 + a573)) * t320));
      *((49 + T1 + b61))    = ((*((D2 + a573)) * t319) + (*((D2 + a572)) * t320));
      t321                  = (t295 + t302);
      t322                  = (t296 - t301);
      t323                  = (t295 - t302);
      t324                  = (t296 + t301);
      t325                  = (s85 + s87);
      t326                  = (s86 - s88);
      t327                  = (s85 - s87);
      t328                  = (s86 + s88);
      t329                  = (t321 + t325);
      t330                  = (t322 + t326);
      t331                  = (t321 - t325);
      t332                  = (t322 - t326);
      a574                  = (b60 + 8);
      a575                  = (b60 + 9);
      a576                  = (b60 + 10);
      a577                  = (b60 + 11);
      *((8 + T1 + b61))     = ((*((D2 + a574)) * t329) - (*((D2 + a575)) * t330));
      *((9 + T1 + b61))     = ((*((D2 + a575)) * t329) + (*((D2 + a574)) * t330));
      *((40 + T1 + b61))    = ((*((D2 + a576)) * t331) - (*((D2 + a577)) * t332));
      *((41 + T1 + b61))    = ((*((D2 + a577)) * t331) + (*((D2 + a576)) * t332));
      t333                  = (t323 + t328);
      t334                  = (t324 - t327);
      t335                  = (t323 - t328);
      t336                  = (t324 + t327);
      a578                  = (b60 + 12);
      a579                  = (b60 + 13);
      a580                  = (b60 + 14);
      a581                  = (b60 + 15);
      *((24 + T1 + b61))    = ((*((D2 + a578)) * t333) - (*((D2 + a579)) * t334));
      *((25 + T1 + b61))    = ((*((D2 + a579)) * t333) + (*((D2 + a578)) * t334));
      *((56 + T1 + b61))    = ((*((D2 + a580)) * t335) - (*((D2 + a581)) * t336));
      *((57 + T1 + b61))    = ((*((D2 + a581)) * t335) + (*((D2 + a580)) * t336));
    }
  }
  for (int i2 = 0; i2 <= 31; i2++) {
    static float T21[128];
    for (int i7 = 0; i7 <= 7; i7++) {
      float a909, a910, a919, a920, s149, s150, s151, s152, t478, t479, t480, t481, t482, t483, t484, t485, t486, t487,
          t488, t489, t490, t491, t492, t493, t494, t495, t496, t497, t498, t499, t500, t501, t502, t503, t504, t505,
          t506, t507, t508, t509, t510, t511, t512, t513, t514, t515, t516, t517, t518, t519, t520, t521;
      int a901, a902, a903, a904, a905, a906, a907, a908, a911, a912, a913, a914, a915, a916, a917, a918, a921, a922,
          a923, a924, a925, a926, a927, a928, a929, a930, a931, a932, a933, a934, a935, a936;
      a901            = ((2 * i2) + (64 * i7));
      a902            = (a901 + 1);
      a903            = (a901 + 2048);
      a904            = (a901 + 2049);
      t478            = (*((T1 + a901)) + *((T1 + a903)));
      t479            = (*((T1 + a902)) + *((T1 + a904)));
      t480            = (*((T1 + a901)) - *((T1 + a903)));
      t481            = (*((T1 + a902)) - *((T1 + a904)));
      a905            = (a901 + 512);
      a906            = (a901 + 513);
      a907            = (a901 + 2560);
      a908            = (a901 + 2561);
      t482            = (*((T1 + a905)) + *((T1 + a907)));
      t483            = (*((T1 + a906)) + *((T1 + a908)));
      a909            = (0.70710678118654757 * (*((T1 + a905)) - *((T1 + a907))));
      a910            = (0.70710678118654757 * (*((T1 + a906)) - *((T1 + a908))));
      s149            = (a909 + a910);
      s150            = (a910 - a909);
      a911            = (a901 + 1024);
      a912            = (a901 + 1025);
      a913            = (a901 + 3072);
      a914            = (a901 + 3073);
      t484            = (*((T1 + a911)) + *((T1 + a913)));
      t485            = (*((T1 + a912)) + *((T1 + a914)));
      t486            = (*((T1 + a911)) - *((T1 + a913)));
      t487            = (*((T1 + a912)) - *((T1 + a914)));
      a915            = (a901 + 1536);
      a916            = (a901 + 1537);
      a917            = (a901 + 3584);
      a918            = (a901 + 3585);
      t488            = (*((T1 + a915)) + *((T1 + a917)));
      t489            = (*((T1 + a916)) + *((T1 + a918)));
      a919            = (0.70710678118654757 * (*((T1 + a916)) - *((T1 + a918))));
      a920            = (0.70710678118654757 * (*((T1 + a915)) - *((T1 + a917))));
      s151            = (a919 - a920);
      s152            = (a920 + a919);
      t490            = (t478 + t484);
      t491            = (t479 + t485);
      t492            = (t478 - t484);
      t493            = (t479 - t485);
      t494            = (t482 + t488);
      t495            = (t483 + t489);
      t496            = (t482 - t488);
      t497            = (t483 - t489);
      t498            = (t490 + t494);
      t499            = (t491 + t495);
      t500            = (t490 - t494);
      t501            = (t491 - t495);
      a921            = (16 * i7);
      a922            = (a921 + 1);
      a923            = (a921 + 2);
      a924            = (a921 + 3);
      *((T21 + a921)) = ((*((D1 + a921)) * t498) - (*((D1 + a922)) * t499));
      *((T21 + a922)) = ((*((D1 + a922)) * t498) + (*((D1 + a921)) * t499));
      a925            = (a921 + 8);
      *((T21 + a925)) = ((*((D1 + a923)) * t500) - (*((D1 + a924)) * t501));
      a926            = (a921 + 9);
      *((T21 + a926)) = ((*((D1 + a924)) * t500) + (*((D1 + a923)) * t501));
      t502            = (t492 + t497);
      t503            = (t493 - t496);
      t504            = (t492 - t497);
      t505            = (t493 + t496);
      a927            = (a921 + 4);
      a928            = (a921 + 5);
      a929            = (a921 + 6);
      a930            = (a921 + 7);
      *((T21 + a927)) = ((*((D1 + a927)) * t502) - (*((D1 + a928)) * t503));
      *((T21 + a928)) = ((*((D1 + a928)) * t502) + (*((D1 + a927)) * t503));
      a931            = (a921 + 12);
      *((T21 + a931)) = ((*((D1 + a929)) * t504) - (*((D1 + a930)) * t505));
      a932            = (a921 + 13);
      *((T21 + a932)) = ((*((D1 + a930)) * t504) + (*((D1 + a929)) * t505));
      t506            = (t480 + t487);
      t507            = (t481 - t486);
      t508            = (t480 - t487);
      t509            = (t481 + t486);
      t510            = (s149 + s151);
      t511            = (s150 - s152);
      t512            = (s149 - s151);
      t513            = (s150 + s152);
      t514            = (t506 + t510);
      t515            = (t507 + t511);
      t516            = (t506 - t510);
      t517            = (t507 - t511);
      a933            = (a921 + 10);
      a934            = (a921 + 11);
      *((T21 + a923)) = ((*((D1 + a925)) * t514) - (*((D1 + a926)) * t515));
      *((T21 + a924)) = ((*((D1 + a926)) * t514) + (*((D1 + a925)) * t515));
      *((T21 + a933)) = ((*((D1 + a933)) * t516) - (*((D1 + a934)) * t517));
      *((T21 + a934)) = ((*((D1 + a934)) * t516) + (*((D1 + a933)) * t517));
      t518            = (t508 + t513);
      t519            = (t509 - t512);
      t520            = (t508 - t513);
      t521            = (t509 + t512);
      a935            = (a921 + 14);
      a936            = (a921 + 15);
      *((T21 + a929)) = ((*((D1 + a931)) * t518) - (*((D1 + a932)) * t519));
      *((T21 + a930)) = ((*((D1 + a932)) * t518) + (*((D1 + a931)) * t519));
      *((T21 + a935)) = ((*((D1 + a935)) * t520) - (*((D1 + a936)) * t521));
      *((T21 + a936)) = ((*((D1 + a936)) * t520) + (*((D1 + a935)) * t521));
    }
    for (int i6 = 0; i6 <= 7; i6++) {
      float a1091, a1092, a1101, a1102, s181, s182, s183, s184, t646, t647, t648, t649, t650, t651, t652, t653, t654,
          t655, t656, t657, t658, t659, t660, t661, t662, t663, t664, t665, t666, t667, t668, t669, t670, t671, t672,
          t673;
      int a1083, a1084, a1085, a1086, a1087, a1088, a1089, a1090, a1093, a1094, a1095, a1096, a1097, a1098, a1099,
          a1100, a1103;
      a1083                 = (2 * i6);
      a1084                 = (a1083 + 1);
      a1085                 = (a1083 + 64);
      a1086                 = (a1083 + 65);
      t646                  = (*((T21 + a1083)) + *((T21 + a1085)));
      t647                  = (*((T21 + a1084)) + *((T21 + a1086)));
      t648                  = (*((T21 + a1083)) - *((T21 + a1085)));
      t649                  = (*((T21 + a1084)) - *((T21 + a1086)));
      a1087                 = (a1083 + 16);
      a1088                 = (a1083 + 17);
      a1089                 = (a1083 + 80);
      a1090                 = (a1083 + 81);
      t650                  = (*((T21 + a1087)) + *((T21 + a1089)));
      t651                  = (*((T21 + a1088)) + *((T21 + a1090)));
      a1091                 = (0.70710678118654757 * (*((T21 + a1087)) - *((T21 + a1089))));
      a1092                 = (0.70710678118654757 * (*((T21 + a1088)) - *((T21 + a1090))));
      s181                  = (a1091 + a1092);
      s182                  = (a1092 - a1091);
      a1093                 = (a1083 + 32);
      a1094                 = (a1083 + 33);
      a1095                 = (a1083 + 96);
      a1096                 = (a1083 + 97);
      t652                  = (*((T21 + a1093)) + *((T21 + a1095)));
      t653                  = (*((T21 + a1094)) + *((T21 + a1096)));
      t654                  = (*((T21 + a1093)) - *((T21 + a1095)));
      t655                  = (*((T21 + a1094)) - *((T21 + a1096)));
      a1097                 = (a1083 + 48);
      a1098                 = (a1083 + 49);
      a1099                 = (a1083 + 112);
      a1100                 = (a1083 + 113);
      t656                  = (*((T21 + a1097)) + *((T21 + a1099)));
      t657                  = (*((T21 + a1098)) + *((T21 + a1100)));
      a1101                 = (0.70710678118654757 * (*((T21 + a1098)) - *((T21 + a1100))));
      a1102                 = (0.70710678118654757 * (*((T21 + a1097)) - *((T21 + a1099))));
      s183                  = (a1101 - a1102);
      s184                  = (a1102 + a1101);
      t658                  = (t646 + t652);
      t659                  = (t647 + t653);
      t660                  = (t646 - t652);
      t661                  = (t647 - t653);
      t662                  = (t650 + t656);
      t663                  = (t651 + t657);
      t664                  = (t650 - t656);
      t665                  = (t651 - t657);
      a1103                 = ((2 * i2) + (64 * i6));
      *((Y + a1103))        = (t658 + t662);
      *((1 + Y + a1103))    = (t659 + t663);
      *((2048 + Y + a1103)) = (t658 - t662);
      *((2049 + Y + a1103)) = (t659 - t663);
      *((1024 + Y + a1103)) = (t660 + t665);
      *((1025 + Y + a1103)) = (t661 - t664);
      *((3072 + Y + a1103)) = (t660 - t665);
      *((3073 + Y + a1103)) = (t661 + t664);
      t666                  = (t648 + t655);
      t667                  = (t649 - t654);
      t668                  = (t648 - t655);
      t669                  = (t649 + t654);
      t670                  = (s181 + s183);
      t671                  = (s182 - s184);
      t672                  = (s181 - s183);
      t673                  = (s182 + s184);
      *((512 + Y + a1103))  = (t666 + t670);
      *((513 + Y + a1103))  = (t667 + t671);
      *((2560 + Y + a1103)) = (t666 - t670);
      *((2561 + Y + a1103)) = (t667 - t671);
      *((1536 + Y + a1103)) = (t668 + t673);
      *((1537 + Y + a1103)) = (t669 - t672);
      *((3584 + Y + a1103)) = (t668 - t673);
      *((3585 + Y + a1103)) = (t669 + t672);
    }
  }
}
}

extern "C" {
void destroy_fftx_dftbat_1_2048_1d_CPU()
{
  /* skip */
}
}
