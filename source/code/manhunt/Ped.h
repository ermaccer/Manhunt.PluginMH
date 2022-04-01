#pragma once
#include "Vector.h"
#include "Collectable.h"
#include "Character.h"
#include "PedHead.h"
#include "Anim.h"
#include "..\RenderWare.h"

enum ePedFlags {
	PF_LOCKONABLE = 0x80000000,
};

class CPed : public CCharacter {
public:
	int field_0;
	char field_4;
	char field_5;
	char field_6;
	char field_7;
	char field_8;
	char field_9;
	char field_A;
	char field_B;
	char field_C;
	char field_D;
	char field_E;
	char field_F;
	char field_10;
	char field_11;
	char field_12;
	char field_13;
	char field_14;
	char field_15;
	char field_16;
	char field_17;
	char field_18;
	char field_19;
	char field_1A;
	char field_1B;
	char field_1C;
	char field_1D;
	char field_1E;
	char field_1F;
	char field_20;
	char field_21;
	char field_22;
	char field_23;
	char field_24;
	char field_25;
	char field_26;
	char field_27;
	char field_28;
	char field_29;
	char field_2A;
	char field_2B;
	char field_2C;
	char field_2D;
	char field_2E;
	char field_2F;
	char field_30;
	char field_31;
	char field_32;
	char field_33;
	char field_34;
	char field_35;
	char field_36;
	char field_37;
	char field_38;
	char field_39;
	char field_3A;
	char field_3B;
	char field_3C;
	char field_3D;
	char field_3E;
	char field_3F;
	char field_40;
	char field_41;
	char field_42;
	char field_43;
	char field_44;
	char field_45;
	char field_46;
	char field_47;
	char field_48;
	char field_49;
	char field_4A;
	char field_4B;
	char field_4C;
	char field_4D;
	char field_4E;
	char field_4F;
	char field_50;
	char field_51;
	char field_52;
	char field_53;
	char field_54;
	char field_55;
	char field_56;
	char field_57;
	char field_58;
	char field_59;
	char field_5A;
	char field_5B;
	char field_5C;
	char field_5D;
	char field_5E;
	char field_5F;
	char field_60;
	char field_61;
	char field_62;
	char field_63;
	char field_64;
	char field_65;
	char field_66;
	char field_67;
	char field_68;
	char field_69;
	char field_6A;
	char field_6B;
	char field_6C;
	char field_6D;
	char field_6E;
	char field_6F;
	char field_70;
	char field_71;
	char field_72;
	char field_73;
	char field_74;
	char field_75;
	char field_76;
	char field_77;
	char field_78;
	char field_79;
	char field_7A;
	char field_7B;
	char field_7C;
	char field_7D;
	char field_7E;
	char field_7F;
	char field_80;
	char field_81;
	char field_82;
	char field_83;
	char field_84;
	char field_85;
	char field_86;
	char field_87;
	char field_88;
	char field_89;
	char field_8A;
	char field_8B;
	char field_8C;
	char field_8D;
	char field_8E;
	char field_8F;
	char field_90;
	char field_91;
	char field_92;
	char field_93;
	char field_94;
	char field_95;
	char field_96;
	char field_97;
	char field_98;
	char field_99;
	char field_9A;
	char field_9B;
	char field_9C;
	char field_9D;
	char field_9E;
	char field_9F;
	char field_A0;
	char field_A1;
	char field_A2;
	char field_A3;
	char field_A4;
	char field_A5;
	char field_A6;
	char field_A7;
	char field_A8;
	char field_A9;
	char field_AA;
	char field_AB;
	char field_AC;
	char field_AD;
	char field_AE;
	char field_AF;
	char field_B0;
	char field_B1;
	char field_B2;
	char field_B3;
	char field_B4;
	char field_B5;
	char field_B6;
	char field_B7;
	char field_B8;
	char field_B9;
	char field_BA;
	char field_BB;
	char field_BC;
	char field_BD;
	char field_BE;
	char field_BF;
	char field_C0;
	char field_C1;
	char field_C2;
	char field_C3;
	char field_C4;
	char field_C5;
	char field_C6;
	char field_C7;
	char field_C8;
	char field_C9;
	char field_CA;
	char field_CB;
	char field_CC;
	char field_CD;
	char field_CE;
	char field_CF;
	char field_D0;
	char field_D1;
	char field_D2;
	char field_D3;
	char field_D4;
	char field_D5;
	char field_D6;
	char field_D7;
	char field_D8;
	char field_D9;
	char field_DA;
	char field_DB;
	char field_DC;
	char field_DD;
	char field_DE;
	char field_DF;
	char field_E0;
	char field_E1;
	char field_E2;
	char field_E3;
	char field_E4;
	char field_E5;
	char field_E6;
	char field_E7;
	char field_E8;
	char field_E9;
	char field_EA;
	char field_EB;
	char field_EC;
	char field_ED;
	char field_EE;
	char field_EF;
	char field_F0;
	char field_F1;
	char field_F2;
	char field_F3;
	char field_F4;
	char field_F5;
	char field_F6;
	char field_F7;
	char field_F8;
	char field_F9;
	char field_FA;
	char field_FB;
	char field_FC;
	char field_FD;
	char field_FE;
	char field_FF;
	char field_100;
	char field_101;
	char field_102;
	char field_103;
	char field_104;
	char field_105;
	char field_106;
	char field_107;
	char field_108;
	char field_109;
	char field_10A;
	char field_10B;
	char field_10C;
	char field_10D;
	char field_10E;
	char field_10F;
	char field_110;
	char field_111;
	char field_112;
	char field_113;
	char field_114;
	char field_115;
	char field_116;
	char field_117;
	char field_118;
	char field_119;
	char field_11A;
	char field_11B;
	char field_11C;
	char field_11D;
	char field_11E;
	char field_11F;
	char field_120;
	char field_121;
	char field_122;
	char field_123;
	int field_124;
	char field_128;
	char field_129;
	char field_12A;
	char field_12B;
	CPedHead *m_pPedHead;
	char field_130;
	char field_131;
	char field_132;
	char field_133;
	CPedBodyAnimFSM* m_pPedBodyAnimFSM;
	int field_138;
	int field_13C;
	int field_140;
	int field_144;
	int field_148;
	char field_14C;
	char field_14D;
	char field_14E;
	char field_14F;
	char field_150;
	char field_151;
	char field_152;
	char field_153;
	char field_154;
	char field_155;
	char field_156;
	char field_157;
	char field_158;
	char field_159;
	char field_15A;
	char field_15B;
	char field_15C;
	char field_15D;
	char field_15E;
	char field_15F;
	char field_160;
	char field_161;
	char field_162;
	char field_163;
	char field_164;
	char field_165;
	char field_166;
	char field_167;
	char field_168;
	char field_169;
	char field_16A;
	char field_16B;
	char field_16C;
	char field_16D;
	char field_16E;
	char field_16F;
	char field_170;
	char field_171;
	char field_172;
	char field_173;
	int m_nPedFlags;
	int field_178;
	float field_17C;
	float field_180;
	int field_184;
	int field_188;
	int field_18C;
	int field_190;
	int field_194;
	int field_198;
	char field_19C;
	char field_19D;
	char field_19E;
	char field_19F;
	int field_1A0;
	int field_1A4;
	int field_1A8;
	int field_1AC;
	int field_1B0;
	float field_1B4;
	int field_1B8;
	char field_1BC;
	char field_1BD;
	char field_1BE;
	char field_1BF;
	char field_1C0;
	char field_1C1;
	char field_1C2;
	char field_1C3;
	char field_1C4;
	char field_1C5;
	char field_1C6;
	char field_1C7;
	char field_1C8;
	char field_1C9;
	char field_1CA;
	char field_1CB;
	char field_1CC;
	char field_1CD;
	char field_1CE;
	char field_1CF;
	char field_1D0;
	char field_1D1;
	char field_1D2;
	char field_1D3;
	char field_1D4;
	char field_1D5;
	char field_1D6;
	char field_1D7;
	char field_1D8;
	char field_1D9;
	char field_1DA;
	char field_1DB;
	char field_1DC;
	char field_1DD;
	char field_1DE;
	char field_1DF;
	char field_1E0;
	char field_1E1;
	char field_1E2;
	char field_1E3;
	char field_1E4;
	char field_1E5;
	char field_1E6;
	char field_1E7;
	char field_1E8;
	char field_1E9;
	char field_1EA;
	char field_1EB;
	char field_1EC;
	char field_1ED;
	char field_1EE;
	char field_1EF;
	char field_1F0;
	char field_1F1;
	char field_1F2;
	char field_1F3;
	char field_1F4;
	char field_1F5;
	char field_1F6;
	char field_1F7;
	char field_1F8;
	char field_1F9;
	char field_1FA;
	char field_1FB;
	char field_1FC;
	char field_1FD;
	char field_1FE;
	char field_1FF;
	char field_200;
	char field_201;
	char field_202;
	char field_203;
	char field_204;
	char field_205;
	char field_206;
	char field_207;
	char field_208;
	char field_209;
	char field_20A;
	char field_20B;
	char field_20C;
	char field_20D;
	char field_20E;
	char field_20F;
	char field_210;
	char field_211;
	char field_212;
	char field_213;
	int field_214;
	char field_218;
	char field_219;
	char field_21A;
	char field_21B;
	char field_21C;
	char field_21D;
	char field_21E;
	char field_21F;
	char field_220;
	char field_221;
	char field_222;
	char field_223;
	char field_224;
	char field_225;
	char field_226;
	char field_227;
	char field_228;
	char field_229;
	char field_22A;
	char field_22B;
	char field_22C;
	char field_22D;
	char field_22E;
	char field_22F;
	char field_230;
	char field_231;
	char field_232;
	char field_233;
	char field_234;
	char field_235;
	char field_236;
	char field_237;
	char field_238;
	char field_239;
	char field_23A;
	char field_23B;
	char field_23C;
	char field_23D;
	char field_23E;
	char field_23F;
	char field_240;
	char field_241;
	char field_242;
	char field_243;
	char field_244;
	char field_245;
	char field_246;
	char field_247;
	char field_248;
	char field_249;
	char field_24A;
	char field_24B;
	char field_24C;
	char field_24D;
	char field_24E;
	char field_24F;
	char field_250;
	char field_251;
	char field_252;
	char field_253;
	char field_254;
	char field_255;
	char field_256;
	char field_257;
	char field_258;
	char field_259;
	char field_25A;
	char field_25B;
	int m_nTextureID;
	int m_bIsTranqed;
	float m_fTranqTime;
	char field_268;
	char field_269;
	char field_26A;
	char field_26B;
	char field_26C;
	char field_26D;
	char field_26E;
	char field_26F;
	char field_270;
	char field_271;
	char field_272;
	char field_273;
	char field_274;
	char field_275;
	char field_276;
	char field_277;
	char field_278;
	char field_279;
	char field_27A;
	char field_27B;
	char field_27C;
	char field_27D;
	char field_27E;
	char field_27F;
	char field_280;
	char field_281;
	char field_282;
	char field_283;
	char field_284;
	char field_285;
	char field_286;
	char field_287;
	char field_288;
	char field_289;
	char field_28A;
	char field_28B;
	char field_28C;
	char field_28D;
	char field_28E;
	char field_28F;
	char field_290;
	char field_291;
	char field_292;
	char field_293;
	char field_294;
	char field_295;
	char field_296;
	char field_297;
	char field_298;
	char field_299;
	char field_29A;
	char field_29B;
	char field_29C;
	char field_29D;
	char field_29E;
	char field_29F;
	char field_2A0;
	char field_2A1;
	char field_2A2;
	char field_2A3;
	char field_2A4;
	char field_2A5;
	char field_2A6;
	char field_2A7;
	char field_2A8;
	char field_2A9;
	char field_2AA;
	char field_2AB;
	char field_2AC;
	char field_2AD;
	char field_2AE;
	char field_2AF;
	char field_2B0;
	char field_2B1;
	char field_2B2;
	char field_2B3;
	int field_2B4;
	char field_2B8;
	char field_2B9;
	char field_2BA;
	char field_2BB;
	char field_2BC;
	char field_2BD;
	char field_2BE;
	char field_2BF;
	char field_2C0;
	char field_2C1;
	char field_2C2;
	char field_2C3;
	char field_2C4;
	char field_2C5;
	char field_2C6;
	char field_2C7;
	char field_2C8;
	char field_2C9;
	char field_2CA;
	char field_2CB;
	float field_2CC;
	float field_2D0;
	float field_2D4;
	float field_2D8;
	char field_2DC;
	char field_2DD;
	char field_2DE;
	char field_2DF;
	char field_2E0;
	char field_2E1;
	char field_2E2;
	char field_2E3;
	int field_2E4;
	int field_2E8;
	char field_2EC;
	char field_2ED;
	char field_2EE;
	char field_2EF;
	char field_2F0;
	char field_2F1;
	char field_2F2;
	char field_2F3;
	char field_2F4;
	char field_2F5;
	char field_2F6;
	char field_2F7;
	char field_2F8;
	char field_2F9;
	char field_2FA;
	char field_2FB;
	char field_2FC;
	char field_2FD;
	char field_2FE;
	char field_2FF;
	char field_300;
	char field_301;
	char field_302;
	char field_303;
	char field_304;
	char field_305;
	char field_306;
	char field_307;
	char field_308;
	char field_309;
	char field_30A;
	char field_30B;
	char field_30C;
	char field_30D;
	char field_30E;
	char field_30F;
	char field_310;
	char field_311;
	char field_312;
	char field_313;
	char field_314;
	char field_315;
	char field_316;
	char field_317;
	char field_318;
	char field_319;
	char field_31A;
	char field_31B;
	char field_31C;
	char field_31D;
	char field_31E;
	char field_31F;
	char field_320;
	char field_321;
	char field_322;
	char field_323;
	char field_324;
	char field_325;
	char field_326;
	char field_327;
	char field_328;
	char field_329;
	char field_32A;
	char field_32B;
	char field_32C;
	char field_32D;
	char field_32E;
	char field_32F;
	char field_330;
	char field_331;
	char field_332;
	char field_333;
	char field_334;
	char field_335;
	char field_336;
	char field_337;
	char field_338;
	char field_339;
	char field_33A;
	char field_33B;
	char field_33C;
	char field_33D;
	char field_33E;
	char field_33F;
	char field_340;
	char field_341;
	char field_342;
	char field_343;
	char field_344;
	char field_345;
	char field_346;
	char field_347;
	char field_348;
	char field_349;
	char field_34A;
	char field_34B;
	char field_34C;
	char field_34D;
	char field_34E;
	char field_34F;
	char field_350;
	char field_351;
	char field_352;
	char field_353;
	char field_354;
	char field_355;
	char field_356;
	char field_357;
	char field_358;
	char field_359;
	char field_35A;
	char field_35B;
	char field_35C;
	char field_35D;
	char field_35E;
	char field_35F;
	int field_360;
	char field_364;
	char field_365;
	char field_366;
	char field_367;
	char field_368;
	char field_369;
	char field_36A;
	char field_36B;
	char field_36C;
	char field_36D;
	char field_36E;
	char field_36F;
	char field_370;
	char field_371;
	char field_372;
	char field_373;
	char field_374;
	char field_375;
	char field_376;
	char field_377;
	char field_378;
	char field_379;
	char field_37A;
	char field_37B;
	char field_37C;
	char field_37D;
	char field_37E;
	char field_37F;
	char field_380;
	char field_381;
	char field_382;
	char field_383;
	char field_384;
	char field_385;
	char field_386;
	char field_387;
	char field_388;
	char field_389;
	char field_38A;
	char field_38B;
	char field_38C;
	char field_38D;
	char field_38E;
	char field_38F;
	char field_390;
	char field_391;
	char field_392;
	char field_393;
	char field_394;
	char field_395;
	char field_396;
	char field_397;
	char field_398;
	char field_399;
	char field_39A;
	char field_39B;
	char field_39C;
	char field_39D;
	char field_39E;
	char field_39F;
	char field_3A0;
	char field_3A1;
	char field_3A2;
	char field_3A3;
	char field_3A4;
	char field_3A5;
	char field_3A6;
	char field_3A7;
	char field_3A8;
	char field_3A9;
	char field_3AA;
	char field_3AB;
	char field_3AC;
	char field_3AD;
	char field_3AE;
	char field_3AF;
	char field_3B0;
	char field_3B1;
	char field_3B2;
	char field_3B3;
	char field_3B4;
	char field_3B5;
	char field_3B6;
	char field_3B7;
	char field_3B8;
	char field_3B9;
	char field_3BA;
	char field_3BB;
	char field_3BC;
	char field_3BD;
	char field_3BE;
	char field_3BF;
	char field_3C0;
	char field_3C1;
	char field_3C2;
	char field_3C3;
	char field_3C4;
	char field_3C5;
	char field_3C6;
	char field_3C7;
	char field_3C8;
	char field_3C9;
	char field_3CA;
	char field_3CB;
	char field_3CC;
	char field_3CD;
	char field_3CE;
	char field_3CF;
	char field_3D0;
	char field_3D1;
	char field_3D2;
	char field_3D3;
	char field_3D4;
	char field_3D5;
	char field_3D6;
	char field_3D7;
	char field_3D8;
	char field_3D9;
	char field_3DA;
	char field_3DB;
	char field_3DC;
	char field_3DD;
	char field_3DE;
	char field_3DF;
	char field_3E0;
	char field_3E1;
	char field_3E2;
	char field_3E3;
	char field_3E4;
	char field_3E5;
	char field_3E6;
	char field_3E7;
	char field_3E8;
	char field_3E9;
	char field_3EA;
	char field_3EB;
	char field_3EC;
	char field_3ED;
	char field_3EE;
	char field_3EF;
	char field_3F0;
	char field_3F1;
	char field_3F2;
	char field_3F3;
	char field_3F4;
	char field_3F5;
	char field_3F6;
	char field_3F7;
	char field_3F8;
	char field_3F9;
	char field_3FA;
	char field_3FB;
	char field_3FC;
	char field_3FD;
	char field_3FE;
	char field_3FF;
	char field_400;
	char field_401;
	char field_402;
	char field_403;
	char field_404;
	char field_405;
	char field_406;
	char field_407;
	char field_408;
	char field_409;
	char field_40A;
	char field_40B;
	char field_40C;
	char field_40D;
	char field_40E;
	char field_40F;
	char field_410;
	char field_411;
	char field_412;
	char field_413;
	char field_414;
	char field_415;
	char field_416;
	char field_417;
	char field_418;
	char field_419;
	char field_41A;
	char field_41B;
	char field_41C;
	char field_41D;
	char field_41E;
	char field_41F;
	char field_420;
	char field_421;
	char field_422;
	char field_423;
	char field_424;
	char field_425;
	char field_426;
	char field_427;
	char field_428;
	char field_429;
	char field_42A;
	char field_42B;
	char field_42C;
	char field_42D;
	char field_42E;
	char field_42F;
	char field_430;
	char field_431;
	char field_432;
	char field_433;
	char field_434;
	char field_435;
	char field_436;
	char field_437;
	char field_438;
	char field_439;
	char field_43A;
	char field_43B;
	char field_43C;
	char field_43D;
	char field_43E;
	char field_43F;
	char field_440;
	char field_441;
	char field_442;
	char field_443;
	char field_444;
	char field_445;
	char field_446;
	char field_447;
	char field_448;
	char field_449;
	char field_44A;
	char field_44B;
	char field_44C;
	char field_44D;
	char field_44E;
	char field_44F;
	char field_450;
	char field_451;
	char field_452;
	char field_453;
	char field_454;
	char field_455;
	char field_456;
	char field_457;
	char field_458;
	char field_459;
	char field_45A;
	char field_45B;
	char field_45C;
	char field_45D;
	char field_45E;
	char field_45F;
	char field_460;
	char field_461;
	char field_462;
	char field_463;
	char field_464;
	char field_465;
	char field_466;
	char field_467;
	char field_468;
	char field_469;
	char field_46A;
	char field_46B;
	char field_46C;
	char field_46D;
	char field_46E;
	char field_46F;
	char field_470;
	char field_471;
	char field_472;
	char field_473;
	char field_474;
	char field_475;
	char field_476;
	char field_477;
	char field_478;
	char field_479;
	char field_47A;
	char field_47B;
	int field_47C;
	char field_480;
	char field_481;
	char field_482;
	char field_483;
	char field_484;
	char field_485;
	char field_486;
	char field_487;
	CVector field_488;
	char field_494;
	char field_495;
	char field_496;
	char field_497;
	char field_498;
	char field_499;
	char field_49A;
	char field_49B;
	char field_49C;
	char field_49D;
	char field_49E;
	char field_49F;
	int field_4A0;
	int field_4A4;
	char field_4A8;
	char field_4A9;
	char field_4AA;
	char field_4AB;
	char field_4AC;
	char field_4AD;
	char field_4AE;
	char field_4AF;
	char field_4B0;
	char field_4B1;
	char field_4B2;
	char field_4B3;

	void ChangePedHead(const char* newHead);
	void ExplodeHead(CVector* pos, int headSelect);
	void SeverHead(CVector* pos);
	void SetHeading(float heading, bool unk);
	void SelectInventoryItem(eHolsterSlot slot, int unk);

	void UseCollectable(eCollectableType item, bool createIfDoesntExist);

	RwFrame* GetBoneFrame(int id);

	bool HoldingMeleeWeapon();
	bool HoldingShooterWeapon();
	bool HoldingTwoHandedShooterWeapon();
	bool HoldingThrowingWeapon();
	bool HoldingClumsyWeapon();
};


class CAutoPed : public CPed {
public:

};