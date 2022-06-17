
/*
 * This code was generated by Spiral 8.4.0-release, www.spiral.net
 */

#include "../omega64.h"
#include <stdint.h>
static float D1[64];
static float D2[2048];
static float D3[64];

extern "C" {
void init_fftx_idftbat_1_1024_1d_CPU()
{
  for (int i7 = 0; i7 <= 7; i7++) {
    for (int i18 = 0; i18 <= 1; i18++) {
      D1[((8 * i7) + (4 * i18))]     = cospi((((float)(2 * (i7 * i18))) / 32));
      D1[(1 + (8 * i7) + (4 * i18))] = sinpi((((float)(2 * (i7 * i18))) / 32));
      D1[(2 + (8 * i7) + (4 * i18))] = cospi((((float)(2 * (i7 * (2 + i18)))) / 32));
      D1[(3 + (8 * i7) + (4 * i18))] = sinpi((((float)(2 * (i7 * (2 + i18)))) / 32));
    }
  }
  for (int i3 = 0; i3 <= 31; i3++) {
    for (int i10 = 0; i10 <= 3; i10++) {
      for (int i22 = 0; i22 <= 1; i22++) {
        for (int i34 = 0; i34 <= 1; i34++) {
          D2[((64 * i3) + (16 * i10) + (8 * i22) + (4 * i34))] =
              cospi((((float)(2 * (i3 * ((8 * i34) + (4 * i22) + i10)))) / 1024));
          D2[(1 + (64 * i3) + (16 * i10) + (8 * i22) + (4 * i34))] =
              sinpi((((float)(2 * (i3 * ((8 * i34) + (4 * i22) + i10)))) / 1024));
          D2[(2 + (64 * i3) + (16 * i10) + (8 * i22) + (4 * i34))] =
              cospi((((float)(2 * (i3 * (16 + (8 * i34) + (4 * i22) + i10)))) / 1024));
          D2[(3 + (64 * i3) + (16 * i10) + (8 * i22) + (4 * i34))] =
              sinpi((((float)(2 * (i3 * (16 + (8 * i34) + (4 * i22) + i10)))) / 1024));
        }
      }
    }
  }
  for (int i11 = 0; i11 <= 7; i11++) {
    for (int i26 = 0; i26 <= 1; i26++) {
      D3[((8 * i11) + (4 * i26))]     = cospi((((float)(2 * (i11 * i26))) / 32));
      D3[(1 + (8 * i11) + (4 * i26))] = sinpi((((float)(2 * (i11 * i26))) / 32));
      D3[(2 + (8 * i11) + (4 * i26))] = cospi((((float)(2 * (i11 * (2 + i26)))) / 32));
      D3[(3 + (8 * i11) + (4 * i26))] = sinpi((((float)(2 * (i11 * (2 + i26)))) / 32));
    }
  }
}
}

extern "C" {
void fftx_idftbat_1_1024_1d_CPU(float* Y, float* X)
{
  static float T1[2048];
  for (int i3 = 0; i3 <= 31; i3++) {
    static float T2[64];
    for (int i11 = 0; i11 <= 7; i11++) {
      float t129, t130, t131, t132, t133, t134, t135, t136, t137, t138, t139, t140, t141, t142, t143, t144;
      int   a154, a155, a156, a157, a158, a159, a160, a161, a162, a163, a164, a165, a166, a167, a168, a169, a170, a171,
          b10;
      a154           = (64 * i11);
      a155           = (2 * i3);
      a156           = (a154 + a155);
      b10            = (a155 + a154);
      a157           = (b10 + 1);
      a158           = (b10 + 1024);
      a159           = (b10 + 1025);
      t129           = (*((X + a156)) + *((X + a158)));
      t130           = (*((X + a157)) + *((X + a159)));
      t131           = (*((X + a156)) - *((X + a158)));
      t132           = (*((X + a157)) - *((X + a159)));
      a160           = (b10 + 512);
      a161           = (b10 + 513);
      a162           = (b10 + 1536);
      a163           = (b10 + 1537);
      t133           = (*((X + a160)) + *((X + a162)));
      t134           = (*((X + a161)) + *((X + a163)));
      t135           = (*((X + a160)) - *((X + a162)));
      t136           = (*((X + a161)) - *((X + a163)));
      t137           = (t129 + t133);
      t138           = (t130 + t134);
      t139           = (t129 - t133);
      t140           = (t130 - t134);
      a164           = (8 * i11);
      a165           = (a164 + 1);
      a166           = (a164 + 2);
      a167           = (a164 + 3);
      *((T2 + a164)) = ((*((D3 + a164)) * t137) - (*((D3 + a165)) * t138));
      *((T2 + a165)) = ((*((D3 + a165)) * t137) + (*((D3 + a164)) * t138));
      a168           = (a164 + 4);
      *((T2 + a168)) = ((*((D3 + a166)) * t139) - (*((D3 + a167)) * t140));
      a169           = (a164 + 5);
      *((T2 + a169)) = ((*((D3 + a167)) * t139) + (*((D3 + a166)) * t140));
      t141           = (t131 - t136);
      t142           = (t132 + t135);
      t143           = (t131 + t136);
      t144           = (t132 - t135);
      a170           = (a164 + 6);
      a171           = (a164 + 7);
      *((T2 + a166)) = ((*((D3 + a168)) * t141) - (*((D3 + a169)) * t142));
      *((T2 + a167)) = ((*((D3 + a169)) * t141) + (*((D3 + a168)) * t142));
      *((T2 + a170)) = ((*((D3 + a170)) * t143) - (*((D3 + a171)) * t144));
      *((T2 + a171)) = ((*((D3 + a171)) * t143) + (*((D3 + a170)) * t144));
    }
    for (int i10 = 0; i10 <= 3; i10++) {
      float a552, a553, a562, a563, s85, s86, s87, s88, t285, t286, t287, t288, t289, t290, t291, t292, t293, t294,
          t295, t296, t297, t298, t299, t300, t301, t302, t303, t304, t305, t306, t307, t308, t309, t310, t311, t312,
          t313, t314, t315, t316, t317, t318, t319, t320, t321, t322, t323, t324, t325, t326, t327, t328;
      int a544, a545, a546, a547, a548, a549, a550, a551, a554, a555, a556, a557, a558, a559, a560, a561, a564, a565,
          a566, a567, a568, a569, a570, a571, a572, a573, a574, a575, a576, a577, a578, a579, a580, a581, b60, b61;
      a544                  = (2 * i10);
      a545                  = (a544 + 1);
      a546                  = (a544 + 32);
      a547                  = (a544 + 33);
      t285                  = (*((T2 + a544)) + *((T2 + a546)));
      t286                  = (*((T2 + a545)) + *((T2 + a547)));
      t287                  = (*((T2 + a544)) - *((T2 + a546)));
      t288                  = (*((T2 + a545)) - *((T2 + a547)));
      a548                  = (a544 + 8);
      a549                  = (a544 + 9);
      a550                  = (a544 + 40);
      a551                  = (a544 + 41);
      t289                  = (*((T2 + a548)) + *((T2 + a550)));
      t290                  = (*((T2 + a549)) + *((T2 + a551)));
      a552                  = (0.70710678118654757 * (*((T2 + a548)) - *((T2 + a550))));
      a553                  = (0.70710678118654757 * (*((T2 + a549)) - *((T2 + a551))));
      s85                   = (a552 - a553);
      s86                   = (a552 + a553);
      a554                  = (a544 + 16);
      a555                  = (a544 + 17);
      a556                  = (a544 + 48);
      a557                  = (a544 + 49);
      t291                  = (*((T2 + a554)) + *((T2 + a556)));
      t292                  = (*((T2 + a555)) + *((T2 + a557)));
      t293                  = (*((T2 + a554)) - *((T2 + a556)));
      t294                  = (*((T2 + a555)) - *((T2 + a557)));
      a558                  = (a544 + 24);
      a559                  = (a544 + 25);
      a560                  = (a544 + 56);
      a561                  = (a544 + 57);
      t295                  = (*((T2 + a558)) + *((T2 + a560)));
      t296                  = (*((T2 + a559)) + *((T2 + a561)));
      a562                  = (0.70710678118654757 * (*((T2 + a558)) - *((T2 + a560))));
      a563                  = (0.70710678118654757 * (*((T2 + a559)) - *((T2 + a561))));
      s87                   = (a562 + a563);
      s88                   = (a562 - a563);
      t297                  = (t285 + t291);
      t298                  = (t286 + t292);
      t299                  = (t285 - t291);
      t300                  = (t286 - t292);
      t301                  = (t289 + t295);
      t302                  = (t290 + t296);
      t303                  = (t289 - t295);
      t304                  = (t290 - t296);
      t305                  = (t297 + t301);
      t306                  = (t298 + t302);
      t307                  = (t297 - t301);
      t308                  = (t298 - t302);
      a564                  = (16 * i10);
      a565                  = (64 * i3);
      a566                  = (a564 + a565);
      b60                   = (a565 + a564);
      a567                  = (b60 + 1);
      a568                  = (b60 + 2);
      a569                  = (b60 + 3);
      *((T1 + a544 + a565)) = ((*((D2 + a566)) * t305) - (*((D2 + a567)) * t306));
      b61                   = (a565 + a544);
      *((1 + T1 + b61))     = ((*((D2 + a567)) * t305) + (*((D2 + a566)) * t306));
      *((32 + T1 + b61))    = ((*((D2 + a568)) * t307) - (*((D2 + a569)) * t308));
      *((33 + T1 + b61))    = ((*((D2 + a569)) * t307) + (*((D2 + a568)) * t308));
      t309                  = (t299 - t304);
      t310                  = (t300 + t303);
      t311                  = (t299 + t304);
      t312                  = (t300 - t303);
      a570                  = (b60 + 4);
      a571                  = (b60 + 5);
      a572                  = (b60 + 6);
      a573                  = (b60 + 7);
      *((16 + T1 + b61))    = ((*((D2 + a570)) * t309) - (*((D2 + a571)) * t310));
      *((17 + T1 + b61))    = ((*((D2 + a571)) * t309) + (*((D2 + a570)) * t310));
      *((48 + T1 + b61))    = ((*((D2 + a572)) * t311) - (*((D2 + a573)) * t312));
      *((49 + T1 + b61))    = ((*((D2 + a573)) * t311) + (*((D2 + a572)) * t312));
      t313                  = (t287 - t294);
      t314                  = (t288 + t293);
      t315                  = (t287 + t294);
      t316                  = (t288 - t293);
      t317                  = (s85 - s87);
      t318                  = (s86 + s88);
      t319                  = (s85 + s87);
      t320                  = (s86 - s88);
      t321                  = (t313 + t317);
      t322                  = (t314 + t318);
      t323                  = (t313 - t317);
      t324                  = (t314 - t318);
      a574                  = (b60 + 8);
      a575                  = (b60 + 9);
      a576                  = (b60 + 10);
      a577                  = (b60 + 11);
      *((8 + T1 + b61))     = ((*((D2 + a574)) * t321) - (*((D2 + a575)) * t322));
      *((9 + T1 + b61))     = ((*((D2 + a575)) * t321) + (*((D2 + a574)) * t322));
      *((40 + T1 + b61))    = ((*((D2 + a576)) * t323) - (*((D2 + a577)) * t324));
      *((41 + T1 + b61))    = ((*((D2 + a577)) * t323) + (*((D2 + a576)) * t324));
      t325                  = (t315 - t320);
      t326                  = (t316 + t319);
      t327                  = (t315 + t320);
      t328                  = (t316 - t319);
      a578                  = (b60 + 12);
      a579                  = (b60 + 13);
      a580                  = (b60 + 14);
      a581                  = (b60 + 15);
      *((24 + T1 + b61))    = ((*((D2 + a578)) * t325) - (*((D2 + a579)) * t326));
      *((25 + T1 + b61))    = ((*((D2 + a579)) * t325) + (*((D2 + a578)) * t326));
      *((56 + T1 + b61))    = ((*((D2 + a580)) * t327) - (*((D2 + a581)) * t328));
      *((57 + T1 + b61))    = ((*((D2 + a581)) * t327) + (*((D2 + a580)) * t328));
    }
  }
  for (int i2 = 0; i2 <= 31; i2++) {
    static float T21[64];
    for (int i7 = 0; i7 <= 7; i7++) {
      float t377, t378, t379, t380, t381, t382, t383, t384, t385, t387, t388, t389, t390, t391, t392, t393;
      int   a733, a734, a735, a736, a737, a738, a739, a740, a741, a742, a743, a744, a745, a746, a747, a748;
      a733            = ((2 * i2) + (64 * i7));
      a734            = (a733 + 1);
      a735            = (a733 + 1024);
      a736            = (a733 + 1025);
      t377            = (*((T1 + a733)) + *((T1 + a735)));
      t378            = (*((T1 + a734)) + *((T1 + a736)));
      t379            = (*((T1 + a733)) - *((T1 + a735)));
      t380            = (*((T1 + a734)) - *((T1 + a736)));
      a737            = (a733 + 512);
      a738            = (a733 + 513);
      a739            = (a733 + 1536);
      a740            = (a733 + 1537);
      t381            = (*((T1 + a737)) + *((T1 + a739)));
      t382            = (*((T1 + a738)) + *((T1 + a740)));
      t383            = (*((T1 + a737)) - *((T1 + a739)));
      t384            = (*((T1 + a738)) - *((T1 + a740)));
      t385            = (t377 + t381);
      t387            = (t378 + t382);
      t388            = (t377 - t381);
      t389            = (t378 - t382);
      a741            = (8 * i7);
      a742            = (a741 + 1);
      a743            = (a741 + 2);
      a744            = (a741 + 3);
      *((T21 + a741)) = ((*((D1 + a741)) * t385) - (*((D1 + a742)) * t387));
      *((T21 + a742)) = ((*((D1 + a742)) * t385) + (*((D1 + a741)) * t387));
      a745            = (a741 + 4);
      *((T21 + a745)) = ((*((D1 + a743)) * t388) - (*((D1 + a744)) * t389));
      a746            = (a741 + 5);
      *((T21 + a746)) = ((*((D1 + a744)) * t388) + (*((D1 + a743)) * t389));
      t390            = (t379 - t384);
      t391            = (t380 + t383);
      t392            = (t379 + t384);
      t393            = (t380 - t383);
      a747            = (a741 + 6);
      a748            = (a741 + 7);
      *((T21 + a743)) = ((*((D1 + a745)) * t390) - (*((D1 + a746)) * t391));
      *((T21 + a744)) = ((*((D1 + a746)) * t390) + (*((D1 + a745)) * t391));
      *((T21 + a747)) = ((*((D1 + a747)) * t392) - (*((D1 + a748)) * t393));
      *((T21 + a748)) = ((*((D1 + a748)) * t392) + (*((D1 + a747)) * t393));
    }
    for (int i6 = 0; i6 <= 3; i6++) {
      float a903, a904, a913, a914, s141, s142, s143, s144, t518, t519, t520, t521, t522, t523, t524, t525, t526, t527,
          t528, t529, t530, t531, t532, t533, t534, t535, t536, t537, t538, t539, t540, t541, t542, t543, t544, t545;
      int a895, a896, a897, a898, a899, a900, a901, a902, a905, a906, a907, a908, a909, a910, a911, a912, a915;
      a895                 = (2 * i6);
      a896                 = (a895 + 1);
      a897                 = (a895 + 32);
      a898                 = (a895 + 33);
      t518                 = (*((T21 + a895)) + *((T21 + a897)));
      t519                 = (*((T21 + a896)) + *((T21 + a898)));
      t520                 = (*((T21 + a895)) - *((T21 + a897)));
      t521                 = (*((T21 + a896)) - *((T21 + a898)));
      a899                 = (a895 + 8);
      a900                 = (a895 + 9);
      a901                 = (a895 + 40);
      a902                 = (a895 + 41);
      t522                 = (*((T21 + a899)) + *((T21 + a901)));
      t523                 = (*((T21 + a900)) + *((T21 + a902)));
      a903                 = (0.70710678118654757 * (*((T21 + a899)) - *((T21 + a901))));
      a904                 = (0.70710678118654757 * (*((T21 + a900)) - *((T21 + a902))));
      s141                 = (a903 - a904);
      s142                 = (a903 + a904);
      a905                 = (a895 + 16);
      a906                 = (a895 + 17);
      a907                 = (a895 + 48);
      a908                 = (a895 + 49);
      t524                 = (*((T21 + a905)) + *((T21 + a907)));
      t525                 = (*((T21 + a906)) + *((T21 + a908)));
      t526                 = (*((T21 + a905)) - *((T21 + a907)));
      t527                 = (*((T21 + a906)) - *((T21 + a908)));
      a909                 = (a895 + 24);
      a910                 = (a895 + 25);
      a911                 = (a895 + 56);
      a912                 = (a895 + 57);
      t528                 = (*((T21 + a909)) + *((T21 + a911)));
      t529                 = (*((T21 + a910)) + *((T21 + a912)));
      a913                 = (0.70710678118654757 * (*((T21 + a909)) - *((T21 + a911))));
      a914                 = (0.70710678118654757 * (*((T21 + a910)) - *((T21 + a912))));
      s143                 = (a913 + a914);
      s144                 = (a913 - a914);
      t530                 = (t518 + t524);
      t531                 = (t519 + t525);
      t532                 = (t518 - t524);
      t533                 = (t519 - t525);
      t534                 = (t522 + t528);
      t535                 = (t523 + t529);
      t536                 = (t522 - t528);
      t537                 = (t523 - t529);
      a915                 = ((2 * i2) + (64 * i6));
      *((Y + a915))        = (t530 + t534);
      *((1 + Y + a915))    = (t531 + t535);
      *((1024 + Y + a915)) = (t530 - t534);
      *((1025 + Y + a915)) = (t531 - t535);
      *((512 + Y + a915))  = (t532 - t537);
      *((513 + Y + a915))  = (t533 + t536);
      *((1536 + Y + a915)) = (t532 + t537);
      *((1537 + Y + a915)) = (t533 - t536);
      t538                 = (t520 - t527);
      t539                 = (t521 + t526);
      t540                 = (t520 + t527);
      t541                 = (t521 - t526);
      t542                 = (s141 - s143);
      t543                 = (s142 + s144);
      t544                 = (s141 + s143);
      t545                 = (s142 - s144);
      *((256 + Y + a915))  = (t538 + t542);
      *((257 + Y + a915))  = (t539 + t543);
      *((1280 + Y + a915)) = (t538 - t542);
      *((1281 + Y + a915)) = (t539 - t543);
      *((768 + Y + a915))  = (t540 - t545);
      *((769 + Y + a915))  = (t541 + t544);
      *((1792 + Y + a915)) = (t540 + t545);
      *((1793 + Y + a915)) = (t541 - t544);
    }
  }
}
}

extern "C" {
void destroy_fftx_idftbat_1_1024_1d_CPU()
{
  /* skip */
}
}
