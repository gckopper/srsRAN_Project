
/*
 * This code was generated by Spiral 8.4.0-release, www.spiral.net
 */

#include "../omega64.h"
#include <stdint.h>
static float D1[32];
static float D2[64];
static float D3[4608];
static float D4[32];
static float D5[64];

extern "C" {
void init_fftx_idftbat_1_2304_1d_CPU()
{
  for (int i7 = 0; i7 <= 7; i7++) {
    for (int i18 = 0; i18 <= 1; i18++) {
      D1[((4 * i7) + (2 * i18))]     = cospi((((float)(2 * (i7 * i18))) / 48));
      D1[(1 + (4 * i7) + (2 * i18))] = sinpi((((float)(2 * (i7 * i18))) / 48));
    }
  }
  for (int i7 = 0; i7 <= 7; i7++) {
    for (int i18 = 0; i18 <= 1; i18++) {
      D2[((8 * i7) + (4 * i18))]     = cospi((((float)(2 * (i7 * (2 + i18)))) / 48));
      D2[(1 + (8 * i7) + (4 * i18))] = sinpi((((float)(2 * (i7 * (2 + i18)))) / 48));
      D2[(2 + (8 * i7) + (4 * i18))] = cospi((((float)(2 * (i7 * (4 + i18)))) / 48));
      D2[(3 + (8 * i7) + (4 * i18))] = sinpi((((float)(2 * (i7 * (4 + i18)))) / 48));
    }
  }
  for (int i3 = 0; i3 <= 47; i3++) {
    for (int i10 = 0; i10 <= 5; i10++) {
      for (int i22 = 0; i22 <= 1; i22++) {
        for (int i37 = 0; i37 <= 1; i37++) {
          D3[((96 * i3) + (16 * i10) + (8 * i22) + (4 * i37))] =
              cospi((((float)(2 * (i3 * ((12 * i37) + (6 * i22) + i10)))) / 2304));
          D3[(1 + (96 * i3) + (16 * i10) + (8 * i22) + (4 * i37))] =
              sinpi((((float)(2 * (i3 * ((12 * i37) + (6 * i22) + i10)))) / 2304));
          D3[(2 + (96 * i3) + (16 * i10) + (8 * i22) + (4 * i37))] =
              cospi((((float)(2 * (i3 * (24 + (12 * i37) + (6 * i22) + i10)))) / 2304));
          D3[(3 + (96 * i3) + (16 * i10) + (8 * i22) + (4 * i37))] =
              sinpi((((float)(2 * (i3 * (24 + (12 * i37) + (6 * i22) + i10)))) / 2304));
        }
      }
    }
  }
  for (int i11 = 0; i11 <= 7; i11++) {
    for (int i26 = 0; i26 <= 1; i26++) {
      D4[((4 * i11) + (2 * i26))]     = cospi((((float)(2 * (i11 * i26))) / 48));
      D4[(1 + (4 * i11) + (2 * i26))] = sinpi((((float)(2 * (i11 * i26))) / 48));
    }
  }
  for (int i11 = 0; i11 <= 7; i11++) {
    for (int i26 = 0; i26 <= 1; i26++) {
      D5[((8 * i11) + (4 * i26))]     = cospi((((float)(2 * (i11 * (2 + i26)))) / 48));
      D5[(1 + (8 * i11) + (4 * i26))] = sinpi((((float)(2 * (i11 * (2 + i26)))) / 48));
      D5[(2 + (8 * i11) + (4 * i26))] = cospi((((float)(2 * (i11 * (4 + i26)))) / 48));
      D5[(3 + (8 * i11) + (4 * i26))] = sinpi((((float)(2 * (i11 * (4 + i26)))) / 48));
    }
  }
}
}

extern "C" {
void fftx_idftbat_1_2304_1d_CPU(float* Y, float* X)
{
  static float T1[4608];
  for (int i3 = 0; i3 <= 47; i3++) {
    static float T2[96];
    for (int i11 = 0; i11 <= 7; i11++) {
      float s100, s85, s86, s87, s88, s89, s90, s91, s92, s93, s94, s95, s96, s97, s98, s99, t177, t178, t179, t180,
          t181, t182, t183, t184, t185, t186, t187, t188, t189, t190, t191, t192, t193, t194, t195, t196, t197, t198,
          t199, t200;
      int a265, a266, a267, a268, a269, a270, a271, a272, a273, a274, a275, a276, a277, a278, a279, a280, a281, a282,
          a283, a284, a285, a286, a287, a288, a289, a290, a291, b14;
      a265                = (96 * i11);
      a266                = (2 * i3);
      a267                = (a265 + a266);
      b14                 = (a266 + a265);
      a268                = (b14 + 1);
      a269                = (b14 + 2304);
      a270                = (b14 + 2305);
      t177                = (*((X + a267)) + *((X + a269)));
      t178                = (*((X + a268)) + *((X + a270)));
      t179                = (*((X + a267)) - *((X + a269)));
      t180                = (*((X + a268)) - *((X + a270)));
      a271                = (b14 + 768);
      a272                = (b14 + 769);
      a273                = (b14 + 3072);
      a274                = (b14 + 3073);
      t181                = (*((X + a271)) + *((X + a273)));
      t182                = (*((X + a272)) + *((X + a274)));
      t183                = (*((X + a271)) - *((X + a273)));
      t184                = (*((X + a272)) - *((X + a274)));
      s85                 = ((0.5 * t183) - (0.8660254037844386 * t184));
      s86                 = ((0.8660254037844386 * t183) + (0.5 * t184));
      a275                = (b14 + 1536);
      a276                = (b14 + 1537);
      a277                = (b14 + 3840);
      a278                = (b14 + 3841);
      t185                = (*((X + a275)) + *((X + a277)));
      t186                = (*((X + a276)) + *((X + a278)));
      t187                = (*((X + a275)) - *((X + a277)));
      t188                = (*((X + a276)) - *((X + a278)));
      s87                 = ((0.5 * t187) + (0.8660254037844386 * t188));
      s88                 = ((0.8660254037844386 * t187) - (0.5 * t188));
      t189                = (t181 + t185);
      t190                = (t182 + t186);
      s89                 = (t177 + t189);
      s90                 = (t178 + t190);
      s91                 = (t177 - (0.5 * t189));
      s92                 = (t178 - (0.5 * t190));
      s93                 = (0.8660254037844386 * (t182 - t186));
      s94                 = (0.8660254037844386 * (t181 - t185));
      a279                = (4 * i11);
      a280                = (a279 + 1);
      a281                = (12 * i11);
      *((T2 + a281))      = ((*((D4 + a279)) * s89) - (*((D4 + a280)) * s90));
      *((1 + T2 + a281))  = ((*((D4 + a280)) * s89) + (*((D4 + a279)) * s90));
      t191                = (s91 - s93);
      t192                = (s92 + s94);
      t193                = (s91 + s93);
      t194                = (s92 - s94);
      a282                = (8 * i11);
      a283                = (a282 + 1);
      a284                = (a282 + 2);
      a285                = (a282 + 3);
      *((4 + T2 + a281))  = ((*((D5 + a282)) * t191) - (*((D5 + a283)) * t192));
      *((5 + T2 + a281))  = ((*((D5 + a283)) * t191) + (*((D5 + a282)) * t192));
      *((8 + T2 + a281))  = ((*((D5 + a284)) * t193) - (*((D5 + a285)) * t194));
      *((9 + T2 + a281))  = ((*((D5 + a285)) * t193) + (*((D5 + a284)) * t194));
      t195                = (s85 - s87);
      t196                = (s86 + s88);
      s95                 = (t179 + t195);
      s96                 = (t180 + t196);
      s97                 = (t179 - (0.5 * t195));
      s98                 = (t180 - (0.5 * t196));
      s99                 = (0.8660254037844386 * (s86 - s88));
      s100                = (0.8660254037844386 * (s85 + s87));
      a286                = (a279 + 2);
      a287                = (a279 + 3);
      *((2 + T2 + a281))  = ((*((D4 + a286)) * s95) - (*((D4 + a287)) * s96));
      *((3 + T2 + a281))  = ((*((D4 + a287)) * s95) + (*((D4 + a286)) * s96));
      t197                = (s97 - s99);
      t198                = (s98 + s100);
      t199                = (s97 + s99);
      t200                = (s98 - s100);
      a288                = (a282 + 4);
      a289                = (a282 + 5);
      a290                = (a282 + 6);
      a291                = (a282 + 7);
      *((6 + T2 + a281))  = ((*((D5 + a288)) * t197) - (*((D5 + a289)) * t198));
      *((7 + T2 + a281))  = ((*((D5 + a289)) * t197) + (*((D5 + a288)) * t198));
      *((10 + T2 + a281)) = ((*((D5 + a290)) * t199) - (*((D5 + a291)) * t200));
      *((11 + T2 + a281)) = ((*((D5 + a291)) * t199) + (*((D5 + a290)) * t200));
    }
    for (int i10 = 0; i10 <= 5; i10++) {
      float a672, a673, a682, a683, s161, s162, s163, s164, t341, t342, t343, t344, t345, t346, t347, t348, t349, t350,
          t351, t352, t353, t354, t355, t356, t357, t358, t359, t360, t361, t362, t363, t364, t365, t366, t367, t368,
          t369, t370, t371, t372, t373, t374, t375, t376, t377, t378, t379, t380, t381, t382, t383, t384;
      int a664, a665, a666, a667, a668, a669, a670, a671, a674, a675, a676, a677, a678, a679, a680, a681, a684, a685,
          a686, a687, a688, a689, a690, a691, a692, a693, a694, a695, a696, a697, a698, a699, a700, a701, b64, b65;
      a664                  = (2 * i10);
      a665                  = (a664 + 1);
      a666                  = (a664 + 48);
      a667                  = (a664 + 49);
      t341                  = (*((T2 + a664)) + *((T2 + a666)));
      t342                  = (*((T2 + a665)) + *((T2 + a667)));
      t343                  = (*((T2 + a664)) - *((T2 + a666)));
      t344                  = (*((T2 + a665)) - *((T2 + a667)));
      a668                  = (a664 + 12);
      a669                  = (a664 + 13);
      a670                  = (a664 + 60);
      a671                  = (a664 + 61);
      t345                  = (*((T2 + a668)) + *((T2 + a670)));
      t346                  = (*((T2 + a669)) + *((T2 + a671)));
      a672                  = (0.70710678118654757 * (*((T2 + a668)) - *((T2 + a670))));
      a673                  = (0.70710678118654757 * (*((T2 + a669)) - *((T2 + a671))));
      s161                  = (a672 - a673);
      s162                  = (a672 + a673);
      a674                  = (a664 + 24);
      a675                  = (a664 + 25);
      a676                  = (a664 + 72);
      a677                  = (a664 + 73);
      t347                  = (*((T2 + a674)) + *((T2 + a676)));
      t348                  = (*((T2 + a675)) + *((T2 + a677)));
      t349                  = (*((T2 + a674)) - *((T2 + a676)));
      t350                  = (*((T2 + a675)) - *((T2 + a677)));
      a678                  = (a664 + 36);
      a679                  = (a664 + 37);
      a680                  = (a664 + 84);
      a681                  = (a664 + 85);
      t351                  = (*((T2 + a678)) + *((T2 + a680)));
      t352                  = (*((T2 + a679)) + *((T2 + a681)));
      a682                  = (0.70710678118654757 * (*((T2 + a678)) - *((T2 + a680))));
      a683                  = (0.70710678118654757 * (*((T2 + a679)) - *((T2 + a681))));
      s163                  = (a682 + a683);
      s164                  = (a682 - a683);
      t353                  = (t341 + t347);
      t354                  = (t342 + t348);
      t355                  = (t341 - t347);
      t356                  = (t342 - t348);
      t357                  = (t345 + t351);
      t358                  = (t346 + t352);
      t359                  = (t345 - t351);
      t360                  = (t346 - t352);
      t361                  = (t353 + t357);
      t362                  = (t354 + t358);
      t363                  = (t353 - t357);
      t364                  = (t354 - t358);
      a684                  = (16 * i10);
      a685                  = (96 * i3);
      a686                  = (a684 + a685);
      b64                   = (a685 + a684);
      a687                  = (b64 + 1);
      a688                  = (b64 + 2);
      a689                  = (b64 + 3);
      *((T1 + a664 + a685)) = ((*((D3 + a686)) * t361) - (*((D3 + a687)) * t362));
      b65                   = (a685 + a664);
      *((1 + T1 + b65))     = ((*((D3 + a687)) * t361) + (*((D3 + a686)) * t362));
      *((48 + T1 + b65))    = ((*((D3 + a688)) * t363) - (*((D3 + a689)) * t364));
      *((49 + T1 + b65))    = ((*((D3 + a689)) * t363) + (*((D3 + a688)) * t364));
      t365                  = (t355 - t360);
      t366                  = (t356 + t359);
      t367                  = (t355 + t360);
      t368                  = (t356 - t359);
      a690                  = (b64 + 4);
      a691                  = (b64 + 5);
      a692                  = (b64 + 6);
      a693                  = (b64 + 7);
      *((24 + T1 + b65))    = ((*((D3 + a690)) * t365) - (*((D3 + a691)) * t366));
      *((25 + T1 + b65))    = ((*((D3 + a691)) * t365) + (*((D3 + a690)) * t366));
      *((72 + T1 + b65))    = ((*((D3 + a692)) * t367) - (*((D3 + a693)) * t368));
      *((73 + T1 + b65))    = ((*((D3 + a693)) * t367) + (*((D3 + a692)) * t368));
      t369                  = (t343 - t350);
      t370                  = (t344 + t349);
      t371                  = (t343 + t350);
      t372                  = (t344 - t349);
      t373                  = (s161 - s163);
      t374                  = (s162 + s164);
      t375                  = (s161 + s163);
      t376                  = (s162 - s164);
      t377                  = (t369 + t373);
      t378                  = (t370 + t374);
      t379                  = (t369 - t373);
      t380                  = (t370 - t374);
      a694                  = (b64 + 8);
      a695                  = (b64 + 9);
      a696                  = (b64 + 10);
      a697                  = (b64 + 11);
      *((12 + T1 + b65))    = ((*((D3 + a694)) * t377) - (*((D3 + a695)) * t378));
      *((13 + T1 + b65))    = ((*((D3 + a695)) * t377) + (*((D3 + a694)) * t378));
      *((60 + T1 + b65))    = ((*((D3 + a696)) * t379) - (*((D3 + a697)) * t380));
      *((61 + T1 + b65))    = ((*((D3 + a697)) * t379) + (*((D3 + a696)) * t380));
      t381                  = (t371 - t376);
      t382                  = (t372 + t375);
      t383                  = (t371 + t376);
      t384                  = (t372 - t375);
      a698                  = (b64 + 12);
      a699                  = (b64 + 13);
      a700                  = (b64 + 14);
      a701                  = (b64 + 15);
      *((36 + T1 + b65))    = ((*((D3 + a698)) * t381) - (*((D3 + a699)) * t382));
      *((37 + T1 + b65))    = ((*((D3 + a699)) * t381) + (*((D3 + a698)) * t382));
      *((84 + T1 + b65))    = ((*((D3 + a700)) * t383) - (*((D3 + a701)) * t384));
      *((85 + T1 + b65))    = ((*((D3 + a701)) * t383) + (*((D3 + a700)) * t384));
    }
  }
  for (int i2 = 0; i2 <= 47; i2++) {
    static float T28[96];
    for (int i7 = 0; i7 <= 7; i7++) {
      float s249, s250, s251, s252, s253, s254, s255, s256, s257, s258, s259, s260, s261, s262, s263, s264, t466, t467,
          t468, t469, t470, t471, t472, t473, t474, t475, t476, t477, t478, t479, t480, t481, t482, t483, t484, t485,
          t486, t487, t488, t489;
      int a964, a965, a966, a967, a968, a969, a970, a971, a972, a973, a974, a975, a976, a977, a978, a979, a980, a981,
          a982, a983, a984, a985, a986, a987, a988;
      a964                 = ((2 * i2) + (96 * i7));
      a965                 = (a964 + 1);
      a966                 = (a964 + 2304);
      a967                 = (a964 + 2305);
      t466                 = (*((T1 + a964)) + *((T1 + a966)));
      t467                 = (*((T1 + a965)) + *((T1 + a967)));
      t468                 = (*((T1 + a964)) - *((T1 + a966)));
      t469                 = (*((T1 + a965)) - *((T1 + a967)));
      a968                 = (a964 + 768);
      a969                 = (a964 + 769);
      a970                 = (a964 + 3072);
      a971                 = (a964 + 3073);
      t470                 = (*((T1 + a968)) + *((T1 + a970)));
      t471                 = (*((T1 + a969)) + *((T1 + a971)));
      t472                 = (*((T1 + a968)) - *((T1 + a970)));
      t473                 = (*((T1 + a969)) - *((T1 + a971)));
      s249                 = ((0.5 * t472) - (0.8660254037844386 * t473));
      s250                 = ((0.8660254037844386 * t472) + (0.5 * t473));
      a972                 = (a964 + 1536);
      a973                 = (a964 + 1537);
      a974                 = (a964 + 3840);
      a975                 = (a964 + 3841);
      t474                 = (*((T1 + a972)) + *((T1 + a974)));
      t475                 = (*((T1 + a973)) + *((T1 + a975)));
      t476                 = (*((T1 + a972)) - *((T1 + a974)));
      t477                 = (*((T1 + a973)) - *((T1 + a975)));
      s251                 = ((0.5 * t476) + (0.8660254037844386 * t477));
      s252                 = ((0.8660254037844386 * t476) - (0.5 * t477));
      t478                 = (t470 + t474);
      t479                 = (t471 + t475);
      s253                 = (t466 + t478);
      s254                 = (t467 + t479);
      s255                 = (t466 - (0.5 * t478));
      s256                 = (t467 - (0.5 * t479));
      s257                 = (0.8660254037844386 * (t471 - t475));
      s258                 = (0.8660254037844386 * (t470 - t474));
      a976                 = (4 * i7);
      a977                 = (a976 + 1);
      a978                 = (12 * i7);
      *((T28 + a978))      = ((*((D1 + a976)) * s253) - (*((D1 + a977)) * s254));
      *((1 + T28 + a978))  = ((*((D1 + a977)) * s253) + (*((D1 + a976)) * s254));
      t480                 = (s255 - s257);
      t481                 = (s256 + s258);
      t482                 = (s255 + s257);
      t483                 = (s256 - s258);
      a979                 = (8 * i7);
      a980                 = (a979 + 1);
      a981                 = (a979 + 2);
      a982                 = (a979 + 3);
      *((4 + T28 + a978))  = ((*((D2 + a979)) * t480) - (*((D2 + a980)) * t481));
      *((5 + T28 + a978))  = ((*((D2 + a980)) * t480) + (*((D2 + a979)) * t481));
      *((8 + T28 + a978))  = ((*((D2 + a981)) * t482) - (*((D2 + a982)) * t483));
      *((9 + T28 + a978))  = ((*((D2 + a982)) * t482) + (*((D2 + a981)) * t483));
      t484                 = (s249 - s251);
      t485                 = (s250 + s252);
      s259                 = (t468 + t484);
      s260                 = (t469 + t485);
      s261                 = (t468 - (0.5 * t484));
      s262                 = (t469 - (0.5 * t485));
      s263                 = (0.8660254037844386 * (s250 - s252));
      s264                 = (0.8660254037844386 * (s249 + s251));
      a983                 = (a976 + 2);
      a984                 = (a976 + 3);
      *((2 + T28 + a978))  = ((*((D1 + a983)) * s259) - (*((D1 + a984)) * s260));
      *((3 + T28 + a978))  = ((*((D1 + a984)) * s259) + (*((D1 + a983)) * s260));
      t486                 = (s261 - s263);
      t487                 = (s262 + s264);
      t488                 = (s261 + s263);
      t489                 = (s262 - s264);
      a985                 = (a979 + 4);
      a986                 = (a979 + 5);
      a987                 = (a979 + 6);
      a988                 = (a979 + 7);
      *((6 + T28 + a978))  = ((*((D2 + a985)) * t486) - (*((D2 + a986)) * t487));
      *((7 + T28 + a978))  = ((*((D2 + a986)) * t486) + (*((D2 + a985)) * t487));
      *((10 + T28 + a978)) = ((*((D2 + a987)) * t488) - (*((D2 + a988)) * t489));
      *((11 + T28 + a978)) = ((*((D2 + a988)) * t488) + (*((D2 + a987)) * t489));
    }
    for (int i6 = 0; i6 <= 5; i6++) {
      float a1143, a1144, a1153, a1154, s293, s294, s295, s296, t614, t615, t616, t617, t618, t619, t620, t621, t622,
          t623, t624, t625, t626, t627, t628, t629, t630, t631, t632, t633, t634, t635, t636, t637, t638, t639, t640,
          t641;
      int a1135, a1136, a1137, a1138, a1139, a1140, a1141, a1142, a1145, a1146, a1147, a1148, a1149, a1150, a1151,
          a1152, a1155;
      a1135                 = (2 * i6);
      a1136                 = (a1135 + 1);
      a1137                 = (a1135 + 48);
      a1138                 = (a1135 + 49);
      t614                  = (*((T28 + a1135)) + *((T28 + a1137)));
      t615                  = (*((T28 + a1136)) + *((T28 + a1138)));
      t616                  = (*((T28 + a1135)) - *((T28 + a1137)));
      t617                  = (*((T28 + a1136)) - *((T28 + a1138)));
      a1139                 = (a1135 + 12);
      a1140                 = (a1135 + 13);
      a1141                 = (a1135 + 60);
      a1142                 = (a1135 + 61);
      t618                  = (*((T28 + a1139)) + *((T28 + a1141)));
      t619                  = (*((T28 + a1140)) + *((T28 + a1142)));
      a1143                 = (0.70710678118654757 * (*((T28 + a1139)) - *((T28 + a1141))));
      a1144                 = (0.70710678118654757 * (*((T28 + a1140)) - *((T28 + a1142))));
      s293                  = (a1143 - a1144);
      s294                  = (a1143 + a1144);
      a1145                 = (a1135 + 24);
      a1146                 = (a1135 + 25);
      a1147                 = (a1135 + 72);
      a1148                 = (a1135 + 73);
      t620                  = (*((T28 + a1145)) + *((T28 + a1147)));
      t621                  = (*((T28 + a1146)) + *((T28 + a1148)));
      t622                  = (*((T28 + a1145)) - *((T28 + a1147)));
      t623                  = (*((T28 + a1146)) - *((T28 + a1148)));
      a1149                 = (a1135 + 36);
      a1150                 = (a1135 + 37);
      a1151                 = (a1135 + 84);
      a1152                 = (a1135 + 85);
      t624                  = (*((T28 + a1149)) + *((T28 + a1151)));
      t625                  = (*((T28 + a1150)) + *((T28 + a1152)));
      a1153                 = (0.70710678118654757 * (*((T28 + a1149)) - *((T28 + a1151))));
      a1154                 = (0.70710678118654757 * (*((T28 + a1150)) - *((T28 + a1152))));
      s295                  = (a1153 + a1154);
      s296                  = (a1153 - a1154);
      t626                  = (t614 + t620);
      t627                  = (t615 + t621);
      t628                  = (t614 - t620);
      t629                  = (t615 - t621);
      t630                  = (t618 + t624);
      t631                  = (t619 + t625);
      t632                  = (t618 - t624);
      t633                  = (t619 - t625);
      a1155                 = ((2 * i2) + (96 * i6));
      *((Y + a1155))        = (t626 + t630);
      *((1 + Y + a1155))    = (t627 + t631);
      *((2304 + Y + a1155)) = (t626 - t630);
      *((2305 + Y + a1155)) = (t627 - t631);
      *((1152 + Y + a1155)) = (t628 - t633);
      *((1153 + Y + a1155)) = (t629 + t632);
      *((3456 + Y + a1155)) = (t628 + t633);
      *((3457 + Y + a1155)) = (t629 - t632);
      t634                  = (t616 - t623);
      t635                  = (t617 + t622);
      t636                  = (t616 + t623);
      t637                  = (t617 - t622);
      t638                  = (s293 - s295);
      t639                  = (s294 + s296);
      t640                  = (s293 + s295);
      t641                  = (s294 - s296);
      *((576 + Y + a1155))  = (t634 + t638);
      *((577 + Y + a1155))  = (t635 + t639);
      *((2880 + Y + a1155)) = (t634 - t638);
      *((2881 + Y + a1155)) = (t635 - t639);
      *((1728 + Y + a1155)) = (t636 - t641);
      *((1729 + Y + a1155)) = (t637 + t640);
      *((4032 + Y + a1155)) = (t636 + t641);
      *((4033 + Y + a1155)) = (t637 - t640);
    }
  }
}
}

extern "C" {
void destroy_fftx_idftbat_1_2304_1d_CPU()
{
  /* skip */
}
}
