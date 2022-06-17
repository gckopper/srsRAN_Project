
/*
 * This code was generated by Spiral 8.4.0-release, www.spiral.net
 */

#include "../omega64.h"
#include <stdint.h>
static float D1[256];
static float D2[24576];
static float D3[192];

extern "C" {
void init_fftx_idftbat_1_12288_1d_CPU()
{
  for (int i7 = 0; i7 <= 15; i7++) {
    for (int i18 = 0; i18 <= 1; i18++) {
      for (int i38 = 0; i38 <= 1; i38++) {
        D1[((16 * i7) + (8 * i18) + (4 * i38))]     = cospi((((float)(2 * (i7 * ((2 * i38) + i18)))) / 128));
        D1[(1 + (16 * i7) + (8 * i18) + (4 * i38))] = sinpi((((float)(2 * (i7 * ((2 * i38) + i18)))) / 128));
        D1[(2 + (16 * i7) + (8 * i18) + (4 * i38))] = cospi((((float)(2 * (i7 * (4 + (2 * i38) + i18)))) / 128));
        D1[(3 + (16 * i7) + (8 * i18) + (4 * i38))] = sinpi((((float)(2 * (i7 * (4 + (2 * i38) + i18)))) / 128));
      }
    }
  }
  for (int i3 = 0; i3 <= 127; i3++) {
    for (int i10 = 0; i10 <= 7; i10++) {
      for (int i22 = 0; i22 <= 2; i22++) {
        for (int i42 = 0; i42 <= 1; i42++) {
          D2[((192 * i3) + (24 * i10) + (8 * i22) + (4 * i42))] =
              cospi((((float)(2 * (i3 * ((24 * i42) + (8 * i22) + i10)))) / 12288));
          D2[(1 + (192 * i3) + (24 * i10) + (8 * i22) + (4 * i42))] =
              sinpi((((float)(2 * (i3 * ((24 * i42) + (8 * i22) + i10)))) / 12288));
          D2[(2 + (192 * i3) + (24 * i10) + (8 * i22) + (4 * i42))] =
              cospi((((float)(2 * (i3 * (48 + (24 * i42) + (8 * i22) + i10)))) / 12288));
          D2[(3 + (192 * i3) + (24 * i10) + (8 * i22) + (4 * i42))] =
              sinpi((((float)(2 * (i3 * (48 + (24 * i42) + (8 * i22) + i10)))) / 12288));
        }
      }
    }
  }
  for (int i11 = 0; i11 <= 11; i11++) {
    for (int i26 = 0; i26 <= 1; i26++) {
      for (int i49 = 0; i49 <= 1; i49++) {
        D3[((16 * i11) + (8 * i26) + (4 * i49))]     = cospi((((float)(2 * (i11 * ((2 * i49) + i26)))) / 96));
        D3[(1 + (16 * i11) + (8 * i26) + (4 * i49))] = sinpi((((float)(2 * (i11 * ((2 * i49) + i26)))) / 96));
        D3[(2 + (16 * i11) + (8 * i26) + (4 * i49))] = cospi((((float)(2 * (i11 * (4 + (2 * i49) + i26)))) / 96));
        D3[(3 + (16 * i11) + (8 * i26) + (4 * i49))] = sinpi((((float)(2 * (i11 * (4 + (2 * i49) + i26)))) / 96));
      }
    }
  }
}
}

extern "C" {
void fftx_idftbat_1_12288_1d_CPU(float* Y, float* X)
{
  static float T1[24576];
  for (int i3 = 0; i3 <= 127; i3++) {
    static float T2[192];
    for (int i11 = 0; i11 <= 11; i11++) {
      float a332, a333, a342, a343, s61, s62, s63, s64, t253, t254, t255, t256, t257, t258, t259, t260, t261, t262,
          t263, t264, t265, t266, t267, t268, t269, t270, t271, t272, t273, t274, t275, t276, t277, t278, t279, t280,
          t281, t282, t283, t284, t285, t286, t287, t288, t289, t290, t291, t292, t293, t294, t295, t296;
      int a322, a323, a324, a325, a326, a327, a328, a329, a330, a331, a334, a335, a336, a337, a338, a339, a340, a341,
          a344, a345, a346, a347, a348, a349, a350, a351, a352, a353, a354, a355, a356, a357, a358, a359, b18;
      a322           = (256 * i11);
      a323           = (2 * i3);
      a324           = (a322 + a323);
      b18            = (a323 + a322);
      a325           = (b18 + 1);
      a326           = (b18 + 12288);
      a327           = (b18 + 12289);
      t253           = (*((X + a324)) + *((X + a326)));
      t254           = (*((X + a325)) + *((X + a327)));
      t255           = (*((X + a324)) - *((X + a326)));
      t256           = (*((X + a325)) - *((X + a327)));
      a328           = (b18 + 3072);
      a329           = (b18 + 3073);
      a330           = (b18 + 15360);
      a331           = (b18 + 15361);
      t257           = (*((X + a328)) + *((X + a330)));
      t258           = (*((X + a329)) + *((X + a331)));
      a332           = (0.70710678118654757 * (*((X + a328)) - *((X + a330))));
      a333           = (0.70710678118654757 * (*((X + a329)) - *((X + a331))));
      s61            = (a332 - a333);
      s62            = (a332 + a333);
      a334           = (b18 + 6144);
      a335           = (b18 + 6145);
      a336           = (b18 + 18432);
      a337           = (b18 + 18433);
      t259           = (*((X + a334)) + *((X + a336)));
      t260           = (*((X + a335)) + *((X + a337)));
      t261           = (*((X + a334)) - *((X + a336)));
      t262           = (*((X + a335)) - *((X + a337)));
      a338           = (b18 + 9216);
      a339           = (b18 + 9217);
      a340           = (b18 + 21504);
      a341           = (b18 + 21505);
      t263           = (*((X + a338)) + *((X + a340)));
      t264           = (*((X + a339)) + *((X + a341)));
      a342           = (0.70710678118654757 * (*((X + a338)) - *((X + a340))));
      a343           = (0.70710678118654757 * (*((X + a339)) - *((X + a341))));
      s63            = (a342 + a343);
      s64            = (a342 - a343);
      t265           = (t253 + t259);
      t266           = (t254 + t260);
      t267           = (t253 - t259);
      t268           = (t254 - t260);
      t269           = (t257 + t263);
      t270           = (t258 + t264);
      t271           = (t257 - t263);
      t272           = (t258 - t264);
      t273           = (t265 + t269);
      t274           = (t266 + t270);
      t275           = (t265 - t269);
      t276           = (t266 - t270);
      a344           = (16 * i11);
      a345           = (a344 + 1);
      a346           = (a344 + 2);
      a347           = (a344 + 3);
      *((T2 + a344)) = ((*((D3 + a344)) * t273) - (*((D3 + a345)) * t274));
      *((T2 + a345)) = ((*((D3 + a345)) * t273) + (*((D3 + a344)) * t274));
      a348           = (a344 + 8);
      *((T2 + a348)) = ((*((D3 + a346)) * t275) - (*((D3 + a347)) * t276));
      a349           = (a344 + 9);
      *((T2 + a349)) = ((*((D3 + a347)) * t275) + (*((D3 + a346)) * t276));
      t277           = (t267 - t272);
      t278           = (t268 + t271);
      t279           = (t267 + t272);
      t280           = (t268 - t271);
      a350           = (a344 + 4);
      a351           = (a344 + 5);
      a352           = (a344 + 6);
      a353           = (a344 + 7);
      *((T2 + a350)) = ((*((D3 + a350)) * t277) - (*((D3 + a351)) * t278));
      *((T2 + a351)) = ((*((D3 + a351)) * t277) + (*((D3 + a350)) * t278));
      a354           = (a344 + 12);
      *((T2 + a354)) = ((*((D3 + a352)) * t279) - (*((D3 + a353)) * t280));
      a355           = (a344 + 13);
      *((T2 + a355)) = ((*((D3 + a353)) * t279) + (*((D3 + a352)) * t280));
      t281           = (t255 - t262);
      t282           = (t256 + t261);
      t283           = (t255 + t262);
      t284           = (t256 - t261);
      t285           = (s61 - s63);
      t286           = (s62 + s64);
      t287           = (s61 + s63);
      t288           = (s62 - s64);
      t289           = (t281 + t285);
      t290           = (t282 + t286);
      t291           = (t281 - t285);
      t292           = (t282 - t286);
      a356           = (a344 + 10);
      a357           = (a344 + 11);
      *((T2 + a346)) = ((*((D3 + a348)) * t289) - (*((D3 + a349)) * t290));
      *((T2 + a347)) = ((*((D3 + a349)) * t289) + (*((D3 + a348)) * t290));
      *((T2 + a356)) = ((*((D3 + a356)) * t291) - (*((D3 + a357)) * t292));
      *((T2 + a357)) = ((*((D3 + a357)) * t291) + (*((D3 + a356)) * t292));
      t293           = (t283 - t288);
      t294           = (t284 + t287);
      t295           = (t283 + t288);
      t296           = (t284 - t287);
      a358           = (a344 + 14);
      a359           = (a344 + 15);
      *((T2 + a352)) = ((*((D3 + a354)) * t293) - (*((D3 + a355)) * t294));
      *((T2 + a353)) = ((*((D3 + a355)) * t293) + (*((D3 + a354)) * t294));
      *((T2 + a358)) = ((*((D3 + a358)) * t295) - (*((D3 + a359)) * t296));
      *((T2 + a359)) = ((*((D3 + a359)) * t295) + (*((D3 + a358)) * t296));
    }
    for (int i10 = 0; i10 <= 7; i10++) {
      float s233, s234, s235, s236, s237, s238, s239, s240, s241, s242, s243, s244, s245, s246, s247, s248, s249, s250,
          s251, s252, s253, s254, s255, s256, s257, s258, s259, s260, s261, s262, s263, s264, t530, t531, t532, t533,
          t534, t535, t536, t537, t538, t539, t540, t541, t542, t543, t544, t545, t546, t547, t548, t549, t550, t551,
          t552, t553, t554, t555, t556, t557, t558, t559, t560, t561, t562, t563, t564, t565, t566, t567, t568, t569,
          t570, t571, t572, t573, t574, t575, t576, t577, t578, t579, t580, t581, t582, t583, t584, t585, t586, t587,
          t588, t589, t590, t591, t592, t593, t594, t595, t596, t597, t598, t599, t600, t601;
      int a940, a941, a942, a943, a944, a945, a946, a947, a948, a949, a950, a951, a952, a953, a954, a955, a956, a957,
          a958, a959, a960, a961, a962, a963, a964, a965, a966, a967, a968, a969, a970, a971, a972, a973, a974, a975,
          a976, a977, a978, a979, a980, a981, a982, a983, a984, a985, a986, a987, a988, a989, b92, b93;
      a940                  = (2 * i10);
      a941                  = (a940 + 1);
      a942                  = (a940 + 64);
      a943                  = (a940 + 65);
      a944                  = (a940 + 128);
      a945                  = (a940 + 129);
      t530                  = (*((T2 + a942)) + *((T2 + a944)));
      t531                  = (*((T2 + a943)) + *((T2 + a945)));
      s233                  = (*((T2 + a940)) + t530);
      s234                  = (*((T2 + a941)) + t531);
      s235                  = (*((T2 + a940)) - (0.5 * t530));
      s236                  = (*((T2 + a941)) - (0.5 * t531));
      s237                  = (0.8660254037844386 * (*((T2 + a943)) - *((T2 + a945))));
      s238                  = (0.8660254037844386 * (*((T2 + a942)) - *((T2 + a944))));
      t532                  = (s235 - s237);
      t533                  = (s236 + s238);
      t534                  = (s235 + s237);
      t535                  = (s236 - s238);
      a946                  = (a940 + 16);
      a947                  = (a940 + 17);
      a948                  = (a940 + 80);
      a949                  = (a940 + 81);
      a950                  = (a940 + 144);
      a951                  = (a940 + 145);
      t536                  = (*((T2 + a948)) + *((T2 + a950)));
      t537                  = (*((T2 + a949)) + *((T2 + a951)));
      s239                  = (*((T2 + a946)) + t536);
      s240                  = (*((T2 + a947)) + t537);
      s241                  = (*((T2 + a946)) - (0.5 * t536));
      s242                  = (*((T2 + a947)) - (0.5 * t537));
      s243                  = (0.8660254037844386 * (*((T2 + a949)) - *((T2 + a951))));
      s244                  = (0.8660254037844386 * (*((T2 + a948)) - *((T2 + a950))));
      t538                  = (s241 - s243);
      t539                  = (s242 + s244);
      t540                  = (s241 + s243);
      t541                  = (s242 - s244);
      s245                  = ((0.8660254037844386 * t538) - (0.5 * t539));
      s246                  = ((0.5 * t538) + (0.8660254037844386 * t539));
      s247                  = ((0.5 * t540) - (0.8660254037844386 * t541));
      s248                  = ((0.8660254037844386 * t540) + (0.5 * t541));
      a952                  = (a940 + 32);
      a953                  = (a940 + 33);
      a954                  = (a940 + 96);
      a955                  = (a940 + 97);
      a956                  = (a940 + 160);
      a957                  = (a940 + 161);
      t542                  = (*((T2 + a954)) + *((T2 + a956)));
      t543                  = (*((T2 + a955)) + *((T2 + a957)));
      s249                  = (*((T2 + a952)) + t542);
      s250                  = (*((T2 + a953)) + t543);
      s251                  = (*((T2 + a952)) - (0.5 * t542));
      s252                  = (*((T2 + a953)) - (0.5 * t543));
      s253                  = (0.8660254037844386 * (*((T2 + a955)) - *((T2 + a957))));
      s254                  = (0.8660254037844386 * (*((T2 + a954)) - *((T2 + a956))));
      t544                  = (s251 - s253);
      t545                  = (s252 + s254);
      t546                  = (s251 + s253);
      t547                  = (s252 - s254);
      s255                  = ((0.5 * t544) - (0.8660254037844386 * t545));
      s256                  = ((0.8660254037844386 * t544) + (0.5 * t545));
      s257                  = ((0.5 * t546) + (0.8660254037844386 * t547));
      s258                  = ((0.8660254037844386 * t546) - (0.5 * t547));
      a958                  = (a940 + 48);
      a959                  = (a940 + 49);
      a960                  = (a940 + 112);
      a961                  = (a940 + 113);
      a962                  = (a940 + 176);
      a963                  = (a940 + 177);
      t548                  = (*((T2 + a960)) + *((T2 + a962)));
      t549                  = (*((T2 + a961)) + *((T2 + a963)));
      s259                  = (*((T2 + a958)) + t548);
      s260                  = (*((T2 + a959)) + t549);
      s261                  = (*((T2 + a958)) - (0.5 * t548));
      s262                  = (*((T2 + a959)) - (0.5 * t549));
      s263                  = (0.8660254037844386 * (*((T2 + a961)) - *((T2 + a963))));
      s264                  = (0.8660254037844386 * (*((T2 + a960)) - *((T2 + a962))));
      t550                  = (s261 - s263);
      t551                  = (s262 + s264);
      t552                  = (s261 + s263);
      t553                  = (s262 - s264);
      t554                  = (s233 + s249);
      t555                  = (s234 + s250);
      t556                  = (s233 - s249);
      t557                  = (s234 - s250);
      t558                  = (s239 + s259);
      t559                  = (s240 + s260);
      t560                  = (s239 - s259);
      t561                  = (s240 - s260);
      t562                  = (t554 + t558);
      t563                  = (t555 + t559);
      t564                  = (t554 - t558);
      t565                  = (t555 - t559);
      a964                  = (24 * i10);
      a965                  = (192 * i3);
      a966                  = (a964 + a965);
      b92                   = (a965 + a964);
      a967                  = (b92 + 1);
      a968                  = (b92 + 2);
      a969                  = (b92 + 3);
      *((T1 + a940 + a965)) = ((*((D2 + a966)) * t562) - (*((D2 + a967)) * t563));
      b93                   = (a965 + a940);
      *((1 + T1 + b93))     = ((*((D2 + a967)) * t562) + (*((D2 + a966)) * t563));
      *((96 + T1 + b93))    = ((*((D2 + a968)) * t564) - (*((D2 + a969)) * t565));
      *((97 + T1 + b93))    = ((*((D2 + a969)) * t564) + (*((D2 + a968)) * t565));
      t566                  = (t556 - t561);
      t567                  = (t557 + t560);
      t568                  = (t556 + t561);
      t569                  = (t557 - t560);
      a970                  = (b92 + 4);
      a971                  = (b92 + 5);
      a972                  = (b92 + 6);
      a973                  = (b92 + 7);
      *((48 + T1 + b93))    = ((*((D2 + a970)) * t566) - (*((D2 + a971)) * t567));
      *((49 + T1 + b93))    = ((*((D2 + a971)) * t566) + (*((D2 + a970)) * t567));
      *((144 + T1 + b93))   = ((*((D2 + a972)) * t568) - (*((D2 + a973)) * t569));
      *((145 + T1 + b93))   = ((*((D2 + a973)) * t568) + (*((D2 + a972)) * t569));
      t570                  = (t532 + s255);
      t571                  = (t533 + s256);
      t572                  = (t532 - s255);
      t573                  = (t533 - s256);
      t574                  = (s245 - t551);
      t575                  = (s246 + t550);
      t576                  = (s245 + t551);
      t577                  = (s246 - t550);
      t578                  = (t570 + t574);
      t579                  = (t571 + t575);
      t580                  = (t570 - t574);
      t581                  = (t571 - t575);
      a974                  = (b92 + 8);
      a975                  = (b92 + 9);
      a976                  = (b92 + 10);
      a977                  = (b92 + 11);
      *((16 + T1 + b93))    = ((*((D2 + a974)) * t578) - (*((D2 + a975)) * t579));
      *((17 + T1 + b93))    = ((*((D2 + a975)) * t578) + (*((D2 + a974)) * t579));
      *((112 + T1 + b93))   = ((*((D2 + a976)) * t580) - (*((D2 + a977)) * t581));
      *((113 + T1 + b93))   = ((*((D2 + a977)) * t580) + (*((D2 + a976)) * t581));
      t582                  = (t572 - t577);
      t583                  = (t573 + t576);
      t584                  = (t572 + t577);
      t585                  = (t573 - t576);
      a978                  = (b92 + 12);
      a979                  = (b92 + 13);
      a980                  = (b92 + 14);
      a981                  = (b92 + 15);
      *((64 + T1 + b93))    = ((*((D2 + a978)) * t582) - (*((D2 + a979)) * t583));
      *((65 + T1 + b93))    = ((*((D2 + a979)) * t582) + (*((D2 + a978)) * t583));
      *((160 + T1 + b93))   = ((*((D2 + a980)) * t584) - (*((D2 + a981)) * t585));
      *((161 + T1 + b93))   = ((*((D2 + a981)) * t584) + (*((D2 + a980)) * t585));
      t586                  = (t534 - s257);
      t587                  = (t535 + s258);
      t588                  = (t534 + s257);
      t589                  = (t535 - s258);
      t590                  = (s247 - t552);
      t591                  = (s248 - t553);
      t592                  = (s247 + t552);
      t593                  = (s248 + t553);
      t594                  = (t586 + t590);
      t595                  = (t587 + t591);
      t596                  = (t586 - t590);
      t597                  = (t587 - t591);
      a982                  = (b92 + 16);
      a983                  = (b92 + 17);
      a984                  = (b92 + 18);
      a985                  = (b92 + 19);
      *((32 + T1 + b93))    = ((*((D2 + a982)) * t594) - (*((D2 + a983)) * t595));
      *((33 + T1 + b93))    = ((*((D2 + a983)) * t594) + (*((D2 + a982)) * t595));
      *((128 + T1 + b93))   = ((*((D2 + a984)) * t596) - (*((D2 + a985)) * t597));
      *((129 + T1 + b93))   = ((*((D2 + a985)) * t596) + (*((D2 + a984)) * t597));
      t598                  = (t588 - t593);
      t599                  = (t589 + t592);
      t600                  = (t588 + t593);
      t601                  = (t589 - t592);
      a986                  = (b92 + 20);
      a987                  = (b92 + 21);
      a988                  = (b92 + 22);
      a989                  = (b92 + 23);
      *((80 + T1 + b93))    = ((*((D2 + a986)) * t598) - (*((D2 + a987)) * t599));
      *((81 + T1 + b93))    = ((*((D2 + a987)) * t598) + (*((D2 + a986)) * t599));
      *((176 + T1 + b93))   = ((*((D2 + a988)) * t600) - (*((D2 + a989)) * t601));
      *((177 + T1 + b93))   = ((*((D2 + a989)) * t600) + (*((D2 + a988)) * t601));
    }
  }
  for (int i2 = 0; i2 <= 95; i2++) {
    static float T32[256];
    for (int i7 = 0; i7 <= 15; i7++) {
      float a1317, a1318, a1327, a1328, s325, s326, s327, s328, t742, t743, t744, t745, t746, t747, t748, t749, t750,
          t751, t752, t753, t754, t755, t756, t757, t758, t759, t760, t761, t762, t763, t764, t765, t766, t767, t768,
          t769, t770, t771, t772, t773, t774, t775, t776, t777, t778, t779, t780, t781, t782, t783, t784, t785;
      int a1309, a1310, a1311, a1312, a1313, a1314, a1315, a1316, a1319, a1320, a1321, a1322, a1323, a1324, a1325,
          a1326, a1329, a1330, a1331, a1332, a1333, a1334, a1335, a1336, a1337, a1338, a1339, a1340, a1341, a1342,
          a1343, a1344;
      a1309            = ((2 * i2) + (192 * i7));
      a1310            = (a1309 + 1);
      a1311            = (a1309 + 12288);
      a1312            = (a1309 + 12289);
      t742             = (*((T1 + a1309)) + *((T1 + a1311)));
      t743             = (*((T1 + a1310)) + *((T1 + a1312)));
      t744             = (*((T1 + a1309)) - *((T1 + a1311)));
      t745             = (*((T1 + a1310)) - *((T1 + a1312)));
      a1313            = (a1309 + 3072);
      a1314            = (a1309 + 3073);
      a1315            = (a1309 + 15360);
      a1316            = (a1309 + 15361);
      t746             = (*((T1 + a1313)) + *((T1 + a1315)));
      t747             = (*((T1 + a1314)) + *((T1 + a1316)));
      a1317            = (0.70710678118654757 * (*((T1 + a1313)) - *((T1 + a1315))));
      a1318            = (0.70710678118654757 * (*((T1 + a1314)) - *((T1 + a1316))));
      s325             = (a1317 - a1318);
      s326             = (a1317 + a1318);
      a1319            = (a1309 + 6144);
      a1320            = (a1309 + 6145);
      a1321            = (a1309 + 18432);
      a1322            = (a1309 + 18433);
      t748             = (*((T1 + a1319)) + *((T1 + a1321)));
      t749             = (*((T1 + a1320)) + *((T1 + a1322)));
      t750             = (*((T1 + a1319)) - *((T1 + a1321)));
      t751             = (*((T1 + a1320)) - *((T1 + a1322)));
      a1323            = (a1309 + 9216);
      a1324            = (a1309 + 9217);
      a1325            = (a1309 + 21504);
      a1326            = (a1309 + 21505);
      t752             = (*((T1 + a1323)) + *((T1 + a1325)));
      t753             = (*((T1 + a1324)) + *((T1 + a1326)));
      a1327            = (0.70710678118654757 * (*((T1 + a1323)) - *((T1 + a1325))));
      a1328            = (0.70710678118654757 * (*((T1 + a1324)) - *((T1 + a1326))));
      s327             = (a1327 + a1328);
      s328             = (a1327 - a1328);
      t754             = (t742 + t748);
      t755             = (t743 + t749);
      t756             = (t742 - t748);
      t757             = (t743 - t749);
      t758             = (t746 + t752);
      t759             = (t747 + t753);
      t760             = (t746 - t752);
      t761             = (t747 - t753);
      t762             = (t754 + t758);
      t763             = (t755 + t759);
      t764             = (t754 - t758);
      t765             = (t755 - t759);
      a1329            = (16 * i7);
      a1330            = (a1329 + 1);
      a1331            = (a1329 + 2);
      a1332            = (a1329 + 3);
      *((T32 + a1329)) = ((*((D1 + a1329)) * t762) - (*((D1 + a1330)) * t763));
      *((T32 + a1330)) = ((*((D1 + a1330)) * t762) + (*((D1 + a1329)) * t763));
      a1333            = (a1329 + 8);
      *((T32 + a1333)) = ((*((D1 + a1331)) * t764) - (*((D1 + a1332)) * t765));
      a1334            = (a1329 + 9);
      *((T32 + a1334)) = ((*((D1 + a1332)) * t764) + (*((D1 + a1331)) * t765));
      t766             = (t756 - t761);
      t767             = (t757 + t760);
      t768             = (t756 + t761);
      t769             = (t757 - t760);
      a1335            = (a1329 + 4);
      a1336            = (a1329 + 5);
      a1337            = (a1329 + 6);
      a1338            = (a1329 + 7);
      *((T32 + a1335)) = ((*((D1 + a1335)) * t766) - (*((D1 + a1336)) * t767));
      *((T32 + a1336)) = ((*((D1 + a1336)) * t766) + (*((D1 + a1335)) * t767));
      a1339            = (a1329 + 12);
      *((T32 + a1339)) = ((*((D1 + a1337)) * t768) - (*((D1 + a1338)) * t769));
      a1340            = (a1329 + 13);
      *((T32 + a1340)) = ((*((D1 + a1338)) * t768) + (*((D1 + a1337)) * t769));
      t770             = (t744 - t751);
      t771             = (t745 + t750);
      t772             = (t744 + t751);
      t773             = (t745 - t750);
      t774             = (s325 - s327);
      t775             = (s326 + s328);
      t776             = (s325 + s327);
      t777             = (s326 - s328);
      t778             = (t770 + t774);
      t779             = (t771 + t775);
      t780             = (t770 - t774);
      t781             = (t771 - t775);
      a1341            = (a1329 + 10);
      a1342            = (a1329 + 11);
      *((T32 + a1331)) = ((*((D1 + a1333)) * t778) - (*((D1 + a1334)) * t779));
      *((T32 + a1332)) = ((*((D1 + a1334)) * t778) + (*((D1 + a1333)) * t779));
      *((T32 + a1341)) = ((*((D1 + a1341)) * t780) - (*((D1 + a1342)) * t781));
      *((T32 + a1342)) = ((*((D1 + a1342)) * t780) + (*((D1 + a1341)) * t781));
      t782             = (t772 - t777);
      t783             = (t773 + t776);
      t784             = (t772 + t777);
      t785             = (t773 - t776);
      a1343            = (a1329 + 14);
      a1344            = (a1329 + 15);
      *((T32 + a1337)) = ((*((D1 + a1339)) * t782) - (*((D1 + a1340)) * t783));
      *((T32 + a1338)) = ((*((D1 + a1340)) * t782) + (*((D1 + a1339)) * t783));
      *((T32 + a1343)) = ((*((D1 + a1343)) * t784) - (*((D1 + a1344)) * t785));
      *((T32 + a1344)) = ((*((D1 + a1344)) * t784) + (*((D1 + a1343)) * t785));
    }
    for (int i6 = 0; i6 <= 7; i6++) {
      float a1683, a1684, a1693, a1694, a1695, a1696, a1705, a1706, s410, s411, s412, s413, s414, s415, s416, s417,
          s418, s419, s420, s421, s422, s423, s424, s425, t1130, t1131, t1132, t1133, t1134, t1135, t1136, t1137, t1138,
          t1139, t1140, t1141, t1142, t1143, t1144, t1145, t1146, t1147, t1148, t1149, t1150, t1151, t1152, t1153,
          t1154, t1155, t1156, t1157, t1158, t1159, t1160, t1161, t1162, t1163, t1164, t1165, t1166, t1167, t1168,
          t1169, t1170, t1171, t1172, t1173, t1174, t1175, t1176, t1177, t1178, t1179, t1180, t1181, t1182, t1183,
          t1184, t1185, t1186, t1187, t1188, t1189, t1190, t1191, t1192, t1193, t1194, t1195, t1196, t1197, t1198,
          t1199, t1200, t1201, t1202, t1203, t1204, t1205, t1206, t1207, t1208, t1209, t1210, t1211, t1212, t1213,
          t1214, t1215, t1216, t1217;
      int a1667, a1668, a1669, a1670, a1671, a1672, a1673, a1674, a1675, a1676, a1677, a1678, a1679, a1680, a1681,
          a1682, a1685, a1686, a1687, a1688, a1689, a1690, a1691, a1692, a1697, a1698, a1699, a1700, a1701, a1702,
          a1703, a1704, a1707;
      a1667                  = (2 * i6);
      a1668                  = (a1667 + 1);
      a1669                  = (a1667 + 128);
      a1670                  = (a1667 + 129);
      t1130                  = (*((T32 + a1667)) + *((T32 + a1669)));
      t1131                  = (*((T32 + a1668)) + *((T32 + a1670)));
      t1132                  = (*((T32 + a1667)) - *((T32 + a1669)));
      t1133                  = (*((T32 + a1668)) - *((T32 + a1670)));
      a1671                  = (a1667 + 64);
      a1672                  = (a1667 + 65);
      a1673                  = (a1667 + 192);
      a1674                  = (a1667 + 193);
      t1134                  = (*((T32 + a1671)) + *((T32 + a1673)));
      t1135                  = (*((T32 + a1672)) + *((T32 + a1674)));
      t1136                  = (*((T32 + a1671)) - *((T32 + a1673)));
      t1137                  = (*((T32 + a1672)) - *((T32 + a1674)));
      t1138                  = (t1130 + t1134);
      t1139                  = (t1131 + t1135);
      t1140                  = (t1130 - t1134);
      t1141                  = (t1131 - t1135);
      t1142                  = (t1132 - t1137);
      t1143                  = (t1133 + t1136);
      t1144                  = (t1132 + t1137);
      t1145                  = (t1133 - t1136);
      a1675                  = (a1667 + 16);
      a1676                  = (a1667 + 17);
      a1677                  = (a1667 + 144);
      a1678                  = (a1667 + 145);
      t1146                  = (*((T32 + a1675)) + *((T32 + a1677)));
      t1147                  = (*((T32 + a1676)) + *((T32 + a1678)));
      t1148                  = (*((T32 + a1675)) - *((T32 + a1677)));
      t1149                  = (*((T32 + a1676)) - *((T32 + a1678)));
      a1679                  = (a1667 + 80);
      a1680                  = (a1667 + 81);
      a1681                  = (a1667 + 208);
      a1682                  = (a1667 + 209);
      t1150                  = (*((T32 + a1679)) + *((T32 + a1681)));
      t1151                  = (*((T32 + a1680)) + *((T32 + a1682)));
      t1152                  = (*((T32 + a1679)) - *((T32 + a1681)));
      t1153                  = (*((T32 + a1680)) - *((T32 + a1682)));
      t1154                  = (t1146 + t1150);
      t1155                  = (t1147 + t1151);
      a1683                  = (0.70710678118654757 * (t1146 - t1150));
      a1684                  = (0.70710678118654757 * (t1147 - t1151));
      s410                   = (a1683 - a1684);
      s411                   = (a1683 + a1684);
      t1156                  = (t1148 - t1153);
      t1157                  = (t1149 + t1152);
      t1158                  = (t1148 + t1153);
      t1159                  = (t1149 - t1152);
      s412                   = ((0.92387953251128674 * t1156) - (0.38268343236508978 * t1157));
      s413                   = ((0.38268343236508978 * t1156) + (0.92387953251128674 * t1157));
      s414                   = ((0.38268343236508978 * t1158) - (0.92387953251128674 * t1159));
      s415                   = ((0.92387953251128674 * t1158) + (0.38268343236508978 * t1159));
      a1685                  = (a1667 + 32);
      a1686                  = (a1667 + 33);
      a1687                  = (a1667 + 160);
      a1688                  = (a1667 + 161);
      t1160                  = (*((T32 + a1685)) + *((T32 + a1687)));
      t1161                  = (*((T32 + a1686)) + *((T32 + a1688)));
      t1162                  = (*((T32 + a1685)) - *((T32 + a1687)));
      t1163                  = (*((T32 + a1686)) - *((T32 + a1688)));
      a1689                  = (a1667 + 96);
      a1690                  = (a1667 + 97);
      a1691                  = (a1667 + 224);
      a1692                  = (a1667 + 225);
      t1164                  = (*((T32 + a1689)) + *((T32 + a1691)));
      t1165                  = (*((T32 + a1690)) + *((T32 + a1692)));
      t1166                  = (*((T32 + a1689)) - *((T32 + a1691)));
      t1167                  = (*((T32 + a1690)) - *((T32 + a1692)));
      t1168                  = (t1160 + t1164);
      t1169                  = (t1161 + t1165);
      t1170                  = (t1160 - t1164);
      t1171                  = (t1161 - t1165);
      a1693                  = (0.70710678118654757 * (t1162 - t1167));
      a1694                  = (0.70710678118654757 * (t1163 + t1166));
      s416                   = (a1693 - a1694);
      s417                   = (a1693 + a1694);
      a1695                  = (0.70710678118654757 * (t1162 + t1167));
      a1696                  = (0.70710678118654757 * (t1163 - t1166));
      s418                   = (a1695 + a1696);
      s419                   = (a1695 - a1696);
      a1697                  = (a1667 + 48);
      a1698                  = (a1667 + 49);
      a1699                  = (a1667 + 176);
      a1700                  = (a1667 + 177);
      t1172                  = (*((T32 + a1697)) + *((T32 + a1699)));
      t1173                  = (*((T32 + a1698)) + *((T32 + a1700)));
      t1174                  = (*((T32 + a1697)) - *((T32 + a1699)));
      t1175                  = (*((T32 + a1698)) - *((T32 + a1700)));
      a1701                  = (a1667 + 112);
      a1702                  = (a1667 + 113);
      a1703                  = (a1667 + 240);
      a1704                  = (a1667 + 241);
      t1176                  = (*((T32 + a1701)) + *((T32 + a1703)));
      t1177                  = (*((T32 + a1702)) + *((T32 + a1704)));
      t1178                  = (*((T32 + a1701)) - *((T32 + a1703)));
      t1179                  = (*((T32 + a1702)) - *((T32 + a1704)));
      t1180                  = (t1172 + t1176);
      t1181                  = (t1173 + t1177);
      a1705                  = (0.70710678118654757 * (t1172 - t1176));
      a1706                  = (0.70710678118654757 * (t1173 - t1177));
      s420                   = (a1705 + a1706);
      s421                   = (a1705 - a1706);
      t1182                  = (t1174 - t1179);
      t1183                  = (t1175 + t1178);
      t1184                  = (t1174 + t1179);
      t1185                  = (t1175 - t1178);
      s422                   = ((0.38268343236508978 * t1182) - (0.92387953251128674 * t1183));
      s423                   = ((0.92387953251128674 * t1182) + (0.38268343236508978 * t1183));
      s424                   = ((0.38268343236508978 * t1185) - (0.92387953251128674 * t1184));
      s425                   = ((0.38268343236508978 * t1184) + (0.92387953251128674 * t1185));
      t1186                  = (t1138 + t1168);
      t1187                  = (t1139 + t1169);
      t1188                  = (t1138 - t1168);
      t1189                  = (t1139 - t1169);
      t1190                  = (t1154 + t1180);
      t1191                  = (t1155 + t1181);
      t1192                  = (t1154 - t1180);
      t1193                  = (t1155 - t1181);
      a1707                  = ((2 * i2) + (192 * i6));
      *((Y + a1707))         = (t1186 + t1190);
      *((1 + Y + a1707))     = (t1187 + t1191);
      *((12288 + Y + a1707)) = (t1186 - t1190);
      *((12289 + Y + a1707)) = (t1187 - t1191);
      *((6144 + Y + a1707))  = (t1188 - t1193);
      *((6145 + Y + a1707))  = (t1189 + t1192);
      *((18432 + Y + a1707)) = (t1188 + t1193);
      *((18433 + Y + a1707)) = (t1189 - t1192);
      t1194                  = (t1142 + s416);
      t1195                  = (t1143 + s417);
      t1196                  = (t1142 - s416);
      t1197                  = (t1143 - s417);
      t1198                  = (s412 + s422);
      t1199                  = (s413 + s423);
      t1200                  = (s412 - s422);
      t1201                  = (s413 - s423);
      *((1536 + Y + a1707))  = (t1194 + t1198);
      *((1537 + Y + a1707))  = (t1195 + t1199);
      *((13824 + Y + a1707)) = (t1194 - t1198);
      *((13825 + Y + a1707)) = (t1195 - t1199);
      *((7680 + Y + a1707))  = (t1196 - t1201);
      *((7681 + Y + a1707))  = (t1197 + t1200);
      *((19968 + Y + a1707)) = (t1196 + t1201);
      *((19969 + Y + a1707)) = (t1197 - t1200);
      t1202                  = (t1140 - t1171);
      t1203                  = (t1141 + t1170);
      t1204                  = (t1140 + t1171);
      t1205                  = (t1141 - t1170);
      t1206                  = (s410 - s420);
      t1207                  = (s411 + s421);
      t1208                  = (s410 + s420);
      t1209                  = (s411 - s421);
      *((3072 + Y + a1707))  = (t1202 + t1206);
      *((3073 + Y + a1707))  = (t1203 + t1207);
      *((15360 + Y + a1707)) = (t1202 - t1206);
      *((15361 + Y + a1707)) = (t1203 - t1207);
      *((9216 + Y + a1707))  = (t1204 - t1209);
      *((9217 + Y + a1707))  = (t1205 + t1208);
      *((21504 + Y + a1707)) = (t1204 + t1209);
      *((21505 + Y + a1707)) = (t1205 - t1208);
      t1210                  = (t1144 - s418);
      t1211                  = (t1145 + s419);
      t1212                  = (t1144 + s418);
      t1213                  = (t1145 - s419);
      t1214                  = (s414 + s424);
      t1215                  = (s415 - s425);
      t1216                  = (s414 - s424);
      t1217                  = (s415 + s425);
      *((4608 + Y + a1707))  = (t1210 + t1214);
      *((4609 + Y + a1707))  = (t1211 + t1215);
      *((16896 + Y + a1707)) = (t1210 - t1214);
      *((16897 + Y + a1707)) = (t1211 - t1215);
      *((10752 + Y + a1707)) = (t1212 - t1217);
      *((10753 + Y + a1707)) = (t1213 + t1216);
      *((23040 + Y + a1707)) = (t1212 + t1217);
      *((23041 + Y + a1707)) = (t1213 - t1216);
    }
  }
}
}

extern "C" {
void destroy_fftx_idftbat_1_12288_1d_CPU()
{
  /* skip */
}
}
