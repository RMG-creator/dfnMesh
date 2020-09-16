//  Geo file generated by Discrete Fracture Network methods 
// Fracture #1 

// POINTS DEFINITION 

Point(1) = {-1,-1,-1};
Point(2) = {1,-1,-1};
Point(3) = {1,1,-1};
Point(4) = {-1,1,-1};
Point(5) = {-1,-1,1};
Point(6) = {1,-1,1};
Point(7) = {1,1,1};
Point(8) = {-1,1,1};
Point(13) = {-1,-0.424365,0.424365};
Point(14) = {-1,-0.424365,-1};
Point(15) = {0.209483,-0.209483,-1};
Point(16) = {0.209483,-0.209483,0.209483};
Point(17) = {0.209483,-0.209483,1};
Point(18) = {-1,-0.424365,1};
Point(19) = {1,-0.0690355,0.0690355};
Point(20) = {1,-0.0690355,-1};
Point(21) = {1,-0.0690355,1};
Point(22) = {0.720617,-0.118672,-0.544296};
Point(23) = {-0.395259,-0.316924,0.684774};


// LINES DEFINITION 

Line(8) = {5,2};
Line(9) = {1,5};
Line(12) = {1,2};
Line(13) = {5,6};
Line(15) = {6,2};
Line(16) = {4,8};
Line(20) = {4,3};
Line(22) = {8,3};
Line(23) = {7,3};
Line(25) = {8,7};
Line(44) = {4,13};
Line(45) = {13,5};
Line(46) = {4,14};
Line(47) = {14,1};
Line(48) = {2,15};
Line(49) = {15,4};
Line(50) = {6,16};
Line(51) = {16,4};
Line(52) = {6,17};
Line(53) = {17,8};
Line(54) = {5,18};
Line(55) = {18,8};
Line(56) = {6,19};
Line(57) = {19,3};
Line(58) = {2,20};
Line(59) = {20,3};
Line(60) = {7,21};
Line(61) = {21,6};
Line(90) = {14,13};
Line(91) = {15,13};
Line(92) = {15,14};
Line(93) = {16,13};
Line(94) = {15,16};
Line(95) = {18,13};
Line(96) = {17,16};
Line(97) = {17,18};
Line(99) = {16,19};
Line(100) = {20,15};
Line(101) = {19,17};
Line(102) = {19,21};
Line(103) = {21,17};
Line(134) = {15,22};
Line(135) = {22,20};
Line(136) = {18,23};
Line(137) = {23,13};
Line(138) = {16,23};
Line(139) = {23,17};
Line(140) = {19,22};
Line(141) = {22,16};
Line(145) = {3,22};


// FACES DEFINITION 

Curve Loop(26) = {-47,-46,44,45,-9};
Plane Surface(26) = {26};
Curve Loop(27) = {48,49,44,45,8};
Plane Surface(27) = {27};
Curve Loop(28) = {12,-8,-9};
Surface(28) = {28};
Curve Loop(29) = {12,48,49,46,47};
Plane Surface(29) = {29};
Curve Loop(30) = {-8,13,15};
Surface(30) = {30};
Curve Loop(31) = {13,50,51,44,45};
Plane Surface(31) = {31};
Curve Loop(32) = {48,49,-51,-50,15};
Plane Surface(32) = {32};
Curve Loop(33) = {-45,-44,16,-55,-54};
Plane Surface(33) = {33};
Curve Loop(34) = {16,-53,-52,50,51};
Plane Surface(34) = {34};
Curve Loop(35) = {13,52,53,-55,-54};
Plane Surface(35) = {35};
Curve Loop(36) = {-15,56,57,-59,-58};
Plane Surface(36) = {36};
Curve Loop(37) = {-51,-50,56,57,-20};
Plane Surface(37) = {37};
Curve Loop(38) = {48,49,20,-59,-58};
Plane Surface(38) = {38};
Curve Loop(39) = {52,53,22,-57,-56};
Plane Surface(39) = {39};
Curve Loop(40) = {16,22,-20};
Surface(40) = {40};
Curve Loop(41) = {-61,-60,23,-57,-56};
Plane Surface(41) = {41};
Curve Loop(42) = {25,23,-22};
Surface(42) = {42};
Curve Loop(43) = {52,53,25,60,61};
Plane Surface(43) = {43};
Curve Loop(108) = {-100,-135,-134};
Surface(108) = {108};
Curve Loop(109) = {95,-137,-136};
Surface(109) = {109};
Curve Loop(110) = {-96,-139,-138};
Surface(110) = {110};
Curve Loop(111) = {-99,-141,-140};
Surface(111) = {111};
Curve Loop(124) = {-91,94,93};
Surface(124) = {124};
Curve Loop(125) = {-93,138,137};
Surface(125) = {125};
Curve Loop(126) = {-94,134,141};
Surface(126) = {126};
Curve Loop(128) = {97,136,139};
Surface(128) = {128};
Curve Loop(129) = {59,145,135};
Surface(129) = {129};
Curve Loop(132) = {-90,-92,91};
Surface(132) = {132};
Curve Loop(133) = {-101,102,103};
Surface(133) = {133};

Physical Surface(3) = {26,27,29,31,32,33,34,35,36,37,38,39,41,43};

Physical Surface("Fractures",2) = {108,109,110,111,124,125,126,128,129,132,133};

Physical Surface(1) = {28,30,40,42};


// EMBEDDED CURVES 

Curve{90} In Surface{26};
Curve{91} In Surface{27};
Curve{92} In Surface{29};
Curve{93} In Surface{31};
Curve{94} In Surface{32};
Curve{95} In Surface{33};
Curve{96} In Surface{34};
Curve{97} In Surface{35};
Curve{ In Surface{36};
Curve{ In Surface{37};
Curve{ In Surface{38};
Curve{ In Surface{39};
Curve{ In Surface{41};
Curve{103} In Surface{43};


// VOLUMES DEFINITION 

Surface Loop(1) = {29,28,27,26};
Volume(1) = {1};
Surface{132} In Volume{1};
Surface Loop(2) = {27,32,31,30};
Volume(2) = {2};
Surface{124} In Volume{2};
Surface Loop(3) = {31,35,34,33};
Volume(3) = {3};
Surface{109,110,125,128} In Volume{3};
Surface Loop(4) = {32,38,37,36};
Volume(4) = {4};
Surface{108,111,126,129} In Volume{4};
Surface Loop(5) = {34,40,39,37};
Volume(5) = {5};
Surface{In Volume{5};
Surface Loop(6) = {43,39,42,41};
Volume(6) = {6};
Surface{133} In Volume{6};

refinedvol[] = {1,2,3,4,5,6};

Physical Volume(1) = {1};
Physical Volume(2) = {2};
Physical Volume(3) = {3};
Physical Volume(4) = {4};
Physical Volume(5) = {5};
Physical Volume(6) = {6};
Transfinite Surface {Physical Surface(1)};
Recombine Surface {Physical Surface(1)};