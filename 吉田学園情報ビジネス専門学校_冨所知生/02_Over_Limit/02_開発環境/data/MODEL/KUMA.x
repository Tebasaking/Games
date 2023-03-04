xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 303;
 0.00000;3.86779;0.00000;,
 0.27060;3.79167;-0.27060;,
 0.00000;3.79167;-0.38268;,
 0.00000;3.86779;0.00000;,
 0.38268;3.79167;0.00000;,
 0.00000;3.86779;0.00000;,
 0.27060;3.79167;0.27060;,
 0.00000;3.86779;0.00000;,
 -0.00000;3.79167;0.38268;,
 0.00000;3.86779;0.00000;,
 -0.27060;3.79167;0.27060;,
 0.00000;3.86779;0.00000;,
 -0.38268;3.79167;-0.00000;,
 0.00000;3.86779;0.00000;,
 -0.27060;3.79167;-0.27060;,
 0.00000;3.86779;0.00000;,
 0.00000;3.79167;-0.38268;,
 0.50000;3.57489;-0.50000;,
 0.00000;3.57489;-0.70711;,
 0.70711;3.57489;0.00000;,
 0.50000;3.57489;0.50000;,
 -0.00000;3.57489;0.70711;,
 -0.50000;3.57489;0.50000;,
 -0.70711;3.57489;-0.00000;,
 -0.50000;3.57489;-0.50000;,
 0.00000;3.57489;-0.70711;,
 0.65328;3.25047;-0.65328;,
 0.00000;3.25047;-0.92388;,
 0.92388;3.25047;0.00000;,
 0.65328;3.25047;0.65328;,
 -0.00000;3.25047;0.92388;,
 -0.65328;3.25047;0.65328;,
 -0.92388;3.25047;-0.00000;,
 -0.65328;3.25047;-0.65328;,
 0.00000;3.25047;-0.92388;,
 0.70711;2.86779;-0.70711;,
 0.00000;2.86779;-1.00000;,
 1.00000;2.86779;0.00000;,
 0.70711;2.86779;0.70711;,
 -0.00000;2.86779;1.00000;,
 -0.70711;2.86779;0.70711;,
 -1.00000;2.86779;-0.00000;,
 -0.70711;2.86779;-0.70711;,
 0.00000;2.86779;-1.00000;,
 0.65328;2.48510;-0.65328;,
 0.00000;2.48510;-0.92388;,
 0.92388;2.48510;0.00000;,
 0.65328;2.48510;0.65328;,
 -0.00000;2.48510;0.92388;,
 -0.65328;2.48510;0.65328;,
 -0.92388;2.48510;-0.00000;,
 -0.65328;2.48510;-0.65328;,
 0.00000;2.48510;-0.92388;,
 0.50000;2.16068;-0.50000;,
 0.00000;2.16068;-0.70711;,
 0.70711;2.16068;0.00000;,
 0.50000;2.16068;0.50000;,
 -0.00000;2.16068;0.70711;,
 -0.50000;2.16068;0.50000;,
 -0.70711;2.16068;-0.00000;,
 -0.50000;2.16068;-0.50000;,
 0.00000;2.16068;-0.70711;,
 0.27060;1.94391;-0.27060;,
 0.00000;1.94391;-0.38268;,
 0.38268;1.94391;0.00000;,
 0.27060;1.94391;0.27060;,
 -0.00000;1.94391;0.38268;,
 -0.27060;1.94391;0.27060;,
 -0.38268;1.94391;-0.00000;,
 -0.27060;1.94391;-0.27060;,
 0.00000;1.94391;-0.38268;,
 0.00000;1.86779;0.00000;,
 0.00000;1.86779;0.00000;,
 0.00000;1.86779;0.00000;,
 0.00000;1.86779;0.00000;,
 0.00000;1.86779;0.00000;,
 0.00000;1.86779;0.00000;,
 0.00000;1.86779;0.00000;,
 0.00000;1.86779;0.00000;,
 -0.28850;2.03046;-0.45400;,
 0.28850;2.03046;-0.45400;,
 0.28850;0.03046;-0.45400;,
 -0.28850;0.03046;-0.45400;,
 0.28850;2.03046;-0.45400;,
 0.28850;2.03046;0.45400;,
 0.28850;0.03046;0.45400;,
 0.28850;0.03046;-0.45400;,
 0.28850;2.03046;0.45400;,
 -0.28850;2.03046;0.45400;,
 -0.28850;0.03046;0.45400;,
 0.28850;0.03046;0.45400;,
 -0.28850;2.03046;0.45400;,
 -0.28850;2.03046;-0.45400;,
 -0.28850;0.03046;-0.45400;,
 -0.28850;0.03046;0.45400;,
 0.28850;2.03046;-0.45400;,
 -0.28850;2.03046;-0.45400;,
 -0.28850;0.03046;-0.45400;,
 0.28850;0.03046;-0.45400;,
 -1.22800;1.96774;-0.45400;,
 1.22800;1.96774;-0.45400;,
 1.22800;1.24074;-0.45400;,
 -1.22800;1.24074;-0.45400;,
 1.22800;1.96774;-0.45400;,
 1.22800;1.96774;0.45400;,
 1.22800;1.24074;0.45400;,
 1.22800;1.24074;-0.45400;,
 1.22800;1.96774;0.45400;,
 -1.22800;1.96774;0.45400;,
 -1.22800;1.24074;0.45400;,
 1.22800;1.24074;0.45400;,
 -1.22800;1.96774;0.45400;,
 -1.22800;1.96774;-0.45400;,
 -1.22800;1.24074;-0.45400;,
 -1.22800;1.24074;0.45400;,
 1.22800;1.96774;-0.45400;,
 -1.22800;1.96774;-0.45400;,
 -1.22800;1.24074;-0.45400;,
 1.22800;1.24074;-0.45400;,
 0.48137;3.11739;-0.75472;,
 0.54009;3.10088;-0.81344;,
 0.48137;3.10088;-0.83777;,
 0.48137;3.11739;-0.75472;,
 0.56442;3.10088;-0.75472;,
 0.48137;3.11739;-0.75472;,
 0.54009;3.10088;-0.69600;,
 0.48137;3.11739;-0.75472;,
 0.48137;3.10088;-0.67168;,
 0.48137;3.11739;-0.75472;,
 0.42265;3.10088;-0.69600;,
 0.48137;3.11739;-0.75472;,
 0.39833;3.10088;-0.75472;,
 0.48137;3.11739;-0.75472;,
 0.42265;3.10088;-0.81344;,
 0.48137;3.11739;-0.75472;,
 0.48137;3.10088;-0.83777;,
 0.58987;3.05384;-0.86322;,
 0.48137;3.05384;-0.90817;,
 0.63482;3.05384;-0.75472;,
 0.58987;3.05384;-0.64622;,
 0.48137;3.05384;-0.60128;,
 0.37287;3.05384;-0.64622;,
 0.32793;3.05384;-0.75472;,
 0.37287;3.05384;-0.86322;,
 0.48137;3.05384;-0.90817;,
 0.62314;2.98344;-0.89649;,
 0.48137;2.98344;-0.95521;,
 0.68186;2.98344;-0.75472;,
 0.62314;2.98344;-0.61296;,
 0.48137;2.98344;-0.55424;,
 0.33961;2.98344;-0.61296;,
 0.28089;2.98344;-0.75472;,
 0.33961;2.98344;-0.89649;,
 0.48137;2.98344;-0.95521;,
 0.63482;2.90039;-0.90817;,
 0.48137;2.90039;-0.97172;,
 0.69837;2.90039;-0.75472;,
 0.63482;2.90039;-0.60128;,
 0.48137;2.90039;-0.53772;,
 0.32793;2.90039;-0.60128;,
 0.26437;2.90039;-0.75472;,
 0.32793;2.90039;-0.90817;,
 0.48137;2.90039;-0.97172;,
 0.62314;2.81735;-0.89649;,
 0.48137;2.81735;-0.95521;,
 0.68186;2.81735;-0.75472;,
 0.62314;2.81735;-0.61296;,
 0.48137;2.81735;-0.55424;,
 0.33961;2.81735;-0.61296;,
 0.28089;2.81735;-0.75472;,
 0.33961;2.81735;-0.89649;,
 0.48137;2.81735;-0.95521;,
 0.58987;2.74695;-0.86322;,
 0.48137;2.74695;-0.90817;,
 0.63482;2.74695;-0.75472;,
 0.58987;2.74695;-0.64622;,
 0.48137;2.74695;-0.60128;,
 0.37287;2.74695;-0.64622;,
 0.32793;2.74695;-0.75472;,
 0.37287;2.74695;-0.86322;,
 0.48137;2.74695;-0.90817;,
 0.54009;2.69991;-0.81344;,
 0.48137;2.69991;-0.83777;,
 0.56442;2.69991;-0.75472;,
 0.54009;2.69991;-0.69600;,
 0.48137;2.69991;-0.67168;,
 0.42265;2.69991;-0.69600;,
 0.39833;2.69991;-0.75472;,
 0.42265;2.69991;-0.81344;,
 0.48137;2.69991;-0.83777;,
 0.48137;2.68339;-0.75472;,
 0.48137;2.68339;-0.75472;,
 0.48137;2.68339;-0.75472;,
 0.48137;2.68339;-0.75472;,
 0.48137;2.68339;-0.75472;,
 0.48137;2.68339;-0.75472;,
 0.48137;2.68339;-0.75472;,
 0.48137;2.68339;-0.75472;,
 -0.37694;3.11739;-0.75472;,
 -0.31822;3.10088;-0.81344;,
 -0.37694;3.10088;-0.83777;,
 -0.37694;3.11739;-0.75472;,
 -0.29389;3.10088;-0.75472;,
 -0.37694;3.11739;-0.75472;,
 -0.31822;3.10088;-0.69600;,
 -0.37694;3.11739;-0.75472;,
 -0.37694;3.10088;-0.67168;,
 -0.37694;3.11739;-0.75472;,
 -0.43566;3.10088;-0.69600;,
 -0.37694;3.11739;-0.75472;,
 -0.45998;3.10088;-0.75472;,
 -0.37694;3.11739;-0.75472;,
 -0.43566;3.10088;-0.81344;,
 -0.37694;3.11739;-0.75472;,
 -0.37694;3.10088;-0.83777;,
 -0.26844;3.05384;-0.86322;,
 -0.37694;3.05384;-0.90817;,
 -0.22349;3.05384;-0.75472;,
 -0.26844;3.05384;-0.64622;,
 -0.37694;3.05384;-0.60128;,
 -0.48544;3.05384;-0.64622;,
 -0.53038;3.05384;-0.75472;,
 -0.48544;3.05384;-0.86322;,
 -0.37694;3.05384;-0.90817;,
 -0.23517;2.98344;-0.89649;,
 -0.37694;2.98344;-0.95521;,
 -0.17646;2.98344;-0.75472;,
 -0.23517;2.98344;-0.61296;,
 -0.37694;2.98344;-0.55424;,
 -0.51870;2.98344;-0.61296;,
 -0.57742;2.98344;-0.75472;,
 -0.51870;2.98344;-0.89649;,
 -0.37694;2.98344;-0.95521;,
 -0.22349;2.90039;-0.90817;,
 -0.37694;2.90039;-0.97172;,
 -0.15994;2.90039;-0.75472;,
 -0.22349;2.90039;-0.60128;,
 -0.37694;2.90039;-0.53772;,
 -0.53038;2.90039;-0.60128;,
 -0.59394;2.90039;-0.75472;,
 -0.53038;2.90039;-0.90817;,
 -0.37694;2.90039;-0.97172;,
 -0.23517;2.81735;-0.89649;,
 -0.37694;2.81735;-0.95521;,
 -0.17646;2.81735;-0.75472;,
 -0.23517;2.81735;-0.61296;,
 -0.37694;2.81735;-0.55424;,
 -0.51870;2.81735;-0.61296;,
 -0.57742;2.81735;-0.75472;,
 -0.51870;2.81735;-0.89649;,
 -0.37694;2.81735;-0.95521;,
 -0.26844;2.74695;-0.86322;,
 -0.37694;2.74695;-0.90817;,
 -0.22349;2.74695;-0.75472;,
 -0.26844;2.74695;-0.64622;,
 -0.37694;2.74695;-0.60128;,
 -0.48544;2.74695;-0.64622;,
 -0.53038;2.74695;-0.75472;,
 -0.48544;2.74695;-0.86322;,
 -0.37694;2.74695;-0.90817;,
 -0.31822;2.69991;-0.81344;,
 -0.37694;2.69991;-0.83777;,
 -0.29389;2.69991;-0.75472;,
 -0.31822;2.69991;-0.69600;,
 -0.37694;2.69991;-0.67168;,
 -0.43566;2.69991;-0.69600;,
 -0.45998;2.69991;-0.75472;,
 -0.43566;2.69991;-0.81344;,
 -0.37694;2.69991;-0.83777;,
 -0.37694;2.68339;-0.75472;,
 -0.37694;2.68339;-0.75472;,
 -0.37694;2.68339;-0.75472;,
 -0.37694;2.68339;-0.75472;,
 -0.37694;2.68339;-0.75472;,
 -0.37694;2.68339;-0.75472;,
 -0.37694;2.68339;-0.75472;,
 -0.37694;2.68339;-0.75472;,
 0.02751;2.30036;-0.99272;,
 0.02751;2.78436;-0.75472;,
 0.19580;2.30036;-0.92302;,
 0.02751;2.78436;-0.75472;,
 0.26551;2.30036;-0.75472;,
 0.02751;2.78436;-0.75472;,
 0.19580;2.30036;-0.58643;,
 0.02751;2.78436;-0.75472;,
 0.02751;2.30036;-0.51672;,
 0.02751;2.78436;-0.75472;,
 -0.14078;2.30036;-0.58643;,
 0.02751;2.78436;-0.75472;,
 -0.21049;2.30036;-0.75472;,
 0.02751;2.78436;-0.75472;,
 -0.14078;2.30036;-0.92302;,
 0.02751;2.78436;-0.75472;,
 0.02751;2.30036;-0.99272;,
 0.02751;2.30036;-0.75472;,
 0.02751;2.30036;-0.99272;,
 0.19580;2.30036;-0.92302;,
 0.26551;2.30036;-0.75472;,
 0.19580;2.30036;-0.58643;,
 0.02751;2.30036;-0.51672;,
 -0.14078;2.30036;-0.58643;,
 -0.21049;2.30036;-0.75472;,
 -0.14078;2.30036;-0.92302;;
 
 220;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;,
 4;79,80,81,82;,
 4;83,84,85,86;,
 4;87,88,89,90;,
 4;91,92,93,94;,
 4;91,84,95,96;,
 4;97,98,85,94;,
 4;99,100,101,102;,
 4;103,104,105,106;,
 4;107,108,109,110;,
 4;111,112,113,114;,
 4;111,104,115,116;,
 4;117,118,105,114;,
 3;119,120,121;,
 3;122,123,120;,
 3;124,125,123;,
 3;126,127,125;,
 3;128,129,127;,
 3;130,131,129;,
 3;132,133,131;,
 3;134,135,133;,
 4;121,120,136,137;,
 4;120,123,138,136;,
 4;123,125,139,138;,
 4;125,127,140,139;,
 4;127,129,141,140;,
 4;129,131,142,141;,
 4;131,133,143,142;,
 4;133,135,144,143;,
 4;137,136,145,146;,
 4;136,138,147,145;,
 4;138,139,148,147;,
 4;139,140,149,148;,
 4;140,141,150,149;,
 4;141,142,151,150;,
 4;142,143,152,151;,
 4;143,144,153,152;,
 4;146,145,154,155;,
 4;145,147,156,154;,
 4;147,148,157,156;,
 4;148,149,158,157;,
 4;149,150,159,158;,
 4;150,151,160,159;,
 4;151,152,161,160;,
 4;152,153,162,161;,
 4;155,154,163,164;,
 4;154,156,165,163;,
 4;156,157,166,165;,
 4;157,158,167,166;,
 4;158,159,168,167;,
 4;159,160,169,168;,
 4;160,161,170,169;,
 4;161,162,171,170;,
 4;164,163,172,173;,
 4;163,165,174,172;,
 4;165,166,175,174;,
 4;166,167,176,175;,
 4;167,168,177,176;,
 4;168,169,178,177;,
 4;169,170,179,178;,
 4;170,171,180,179;,
 4;173,172,181,182;,
 4;172,174,183,181;,
 4;174,175,184,183;,
 4;175,176,185,184;,
 4;176,177,186,185;,
 4;177,178,187,186;,
 4;178,179,188,187;,
 4;179,180,189,188;,
 3;182,181,190;,
 3;181,183,191;,
 3;183,184,192;,
 3;184,185,193;,
 3;185,186,194;,
 3;186,187,195;,
 3;187,188,196;,
 3;188,189,197;,
 3;198,199,200;,
 3;201,202,199;,
 3;203,204,202;,
 3;205,206,204;,
 3;207,208,206;,
 3;209,210,208;,
 3;211,212,210;,
 3;213,214,212;,
 4;200,199,215,216;,
 4;199,202,217,215;,
 4;202,204,218,217;,
 4;204,206,219,218;,
 4;206,208,220,219;,
 4;208,210,221,220;,
 4;210,212,222,221;,
 4;212,214,223,222;,
 4;216,215,224,225;,
 4;215,217,226,224;,
 4;217,218,227,226;,
 4;218,219,228,227;,
 4;219,220,229,228;,
 4;220,221,230,229;,
 4;221,222,231,230;,
 4;222,223,232,231;,
 4;225,224,233,234;,
 4;224,226,235,233;,
 4;226,227,236,235;,
 4;227,228,237,236;,
 4;228,229,238,237;,
 4;229,230,239,238;,
 4;230,231,240,239;,
 4;231,232,241,240;,
 4;234,233,242,243;,
 4;233,235,244,242;,
 4;235,236,245,244;,
 4;236,237,246,245;,
 4;237,238,247,246;,
 4;238,239,248,247;,
 4;239,240,249,248;,
 4;240,241,250,249;,
 4;243,242,251,252;,
 4;242,244,253,251;,
 4;244,245,254,253;,
 4;245,246,255,254;,
 4;246,247,256,255;,
 4;247,248,257,256;,
 4;248,249,258,257;,
 4;249,250,259,258;,
 4;252,251,260,261;,
 4;251,253,262,260;,
 4;253,254,263,262;,
 4;254,255,264,263;,
 4;255,256,265,264;,
 4;256,257,266,265;,
 4;257,258,267,266;,
 4;258,259,268,267;,
 3;261,260,269;,
 3;260,262,270;,
 3;262,263,271;,
 3;263,264,272;,
 3;264,265,273;,
 3;265,266,274;,
 3;266,267,275;,
 3;267,268,276;,
 3;277,278,279;,
 3;279,280,281;,
 3;281,282,283;,
 3;283,284,285;,
 3;285,286,287;,
 3;287,288,289;,
 3;289,290,291;,
 3;291,292,293;,
 3;294,295,296;,
 3;294,296,297;,
 3;294,297,298;,
 3;294,298,299;,
 3;294,299,300;,
 3;294,300,301;,
 3;294,301,302;,
 3;294,302,295;;
 
 MeshMaterialList {
  1;
  220;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  180;
  -0.000000;1.000000;0.000000;,
  0.000000;0.924735;-0.380611;,
  0.269132;0.924735;-0.269132;,
  0.380611;0.924735;0.000000;,
  0.269132;0.924735;0.269132;,
  -0.000000;0.924735;0.380611;,
  -0.269132;0.924735;0.269132;,
  -0.380611;0.924735;-0.000000;,
  -0.269132;0.924735;-0.269132;,
  0.000000;0.709230;-0.704977;,
  0.498494;0.709230;-0.498494;,
  0.704977;0.709231;0.000000;,
  0.498494;0.709231;0.498494;,
  -0.000000;0.709230;0.704977;,
  -0.498494;0.709230;0.498494;,
  -0.704977;0.709230;0.000000;,
  -0.498494;0.709230;-0.498494;,
  -0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  -0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;-0.000000;,
  -0.652733;0.384551;-0.652733;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;-0.000000;,
  -0.707107;-0.000000;-0.707107;,
  -0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;0.000000;,
  0.652733;-0.384551;0.652733;,
  -0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;-0.000000;,
  -0.652733;-0.384551;-0.652733;,
  -0.000000;-0.709230;-0.704977;,
  0.498494;-0.709230;-0.498494;,
  0.704977;-0.709230;0.000000;,
  0.498494;-0.709230;0.498494;,
  -0.000000;-0.709230;0.704977;,
  -0.498494;-0.709230;0.498494;,
  -0.704977;-0.709230;-0.000000;,
  -0.498494;-0.709230;-0.498494;,
  -0.000000;-0.924735;-0.380611;,
  0.269133;-0.924735;-0.269133;,
  0.380611;-0.924735;0.000000;,
  0.269133;-0.924735;0.269133;,
  -0.000000;-0.924735;0.380611;,
  -0.269133;-0.924735;0.269132;,
  -0.380611;-0.924735;-0.000000;,
  -0.269133;-0.924735;-0.269132;,
  -0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;1.000000;0.000000;,
  0.000000;0.924735;-0.380612;,
  0.269133;0.924735;-0.269133;,
  0.380612;0.924735;0.000000;,
  0.269133;0.924735;0.269133;,
  0.000000;0.924735;0.380612;,
  -0.269133;0.924735;0.269133;,
  -0.380612;0.924735;0.000000;,
  -0.269133;0.924735;-0.269133;,
  0.000000;0.709230;-0.704977;,
  0.498494;0.709230;-0.498494;,
  0.704977;0.709230;0.000000;,
  0.498494;0.709230;0.498494;,
  -0.000000;0.709230;0.704977;,
  -0.498494;0.709230;0.498494;,
  -0.704977;0.709230;0.000000;,
  -0.498494;0.709230;-0.498494;,
  0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  -0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652733;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  0.707107;-0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;-0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;-0.000000;-0.707107;,
  0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;-0.000000;,
  0.652733;-0.384551;0.652733;,
  -0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;0.000000;,
  -0.652733;-0.384551;-0.652733;,
  0.000000;-0.709230;-0.704977;,
  0.498494;-0.709230;-0.498494;,
  0.704977;-0.709230;-0.000000;,
  0.498494;-0.709230;0.498494;,
  -0.000000;-0.709230;0.704977;,
  -0.498494;-0.709230;0.498494;,
  -0.704977;-0.709230;0.000000;,
  -0.498494;-0.709230;-0.498494;,
  0.000000;-0.924735;-0.380612;,
  0.269133;-0.924735;-0.269133;,
  0.380612;-0.924735;-0.000000;,
  0.269133;-0.924735;0.269133;,
  0.000000;-0.924735;0.380612;,
  -0.269133;-0.924735;0.269133;,
  -0.380612;-0.924735;0.000000;,
  -0.269133;-0.924735;-0.269133;,
  -0.000000;-1.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  0.269133;0.924735;-0.269133;,
  0.380612;0.924735;0.000000;,
  0.269133;0.924735;0.269133;,
  -0.269133;0.924735;0.269133;,
  -0.380612;0.924735;0.000000;,
  -0.269133;0.924735;-0.269133;,
  0.000000;0.709230;-0.704977;,
  0.498494;0.709230;-0.498494;,
  0.704977;0.709230;0.000000;,
  0.498494;0.709230;0.498494;,
  -0.000000;0.709230;0.704977;,
  -0.498494;0.709230;0.498494;,
  -0.704977;0.709230;0.000000;,
  -0.498494;0.709230;-0.498494;,
  0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  -0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  0.000000;-0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;0.707107;,
  0.000000;-0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;-0.000000;,
  0.652733;-0.384551;0.652733;,
  -0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;0.000000;,
  0.000000;-0.709230;-0.704977;,
  0.498494;-0.709230;-0.498494;,
  0.704977;-0.709230;-0.000000;,
  0.498494;-0.709230;0.498494;,
  -0.000000;-0.709230;0.704977;,
  -0.498494;-0.709230;0.498494;,
  -0.704977;-0.709230;0.000000;,
  -0.498494;-0.709230;-0.498494;,
  0.000000;-0.924735;-0.380612;,
  0.269133;-0.924735;-0.269133;,
  0.380612;-0.924735;-0.000000;,
  0.269133;-0.924735;0.269133;,
  0.000000;-0.924735;0.380612;,
  -0.269133;-0.924735;0.269133;,
  -0.380612;-0.924735;0.000000;,
  -0.269133;-0.924735;-0.269133;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.441271;-0.897374;,
  0.634539;0.441271;-0.634539;,
  0.897374;0.441271;0.000000;,
  0.634539;0.441271;0.634539;,
  -0.000000;0.441271;0.897374;,
  -0.634539;0.441271;0.634539;,
  -0.897374;0.441271;0.000000;,
  -0.634539;0.441271;-0.634539;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;;
  220;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;145,145,145,145;,
  4;179,179,179,179;,
  4;178,178,178,178;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;145,145,145,145;,
  4;179,179,179,179;,
  4;178,178,178,178;,
  3;61,63,62;,
  3;61,64,63;,
  3;61,65,64;,
  3;61,66,65;,
  3;61,67,66;,
  3;61,68,67;,
  3;61,69,68;,
  3;61,62,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,65,73,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,62,70,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,73,81,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,70,78,85;,
  4;78,79,87,86;,
  4;79,80,59,87;,
  4;80,81,88,59;,
  4;81,82,89,88;,
  4;82,83,90,89;,
  4;83,84,91,90;,
  4;84,85,92,91;,
  4;85,78,86,92;,
  4;86,87,94,93;,
  4;87,59,95,94;,
  4;59,88,96,95;,
  4;88,89,97,96;,
  4;89,90,98,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,86,93,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,98,106,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,93,101,108;,
  4;101,102,110,109;,
  4;102,103,111,110;,
  4;103,104,112,111;,
  4;104,105,113,112;,
  4;105,106,114,113;,
  4;106,107,115,114;,
  4;107,108,116,115;,
  4;108,101,109,116;,
  3;109,110,117;,
  3;110,111,117;,
  3;111,112,117;,
  3;112,113,117;,
  3;113,114,117;,
  3;114,115,117;,
  3;115,116,117;,
  3;116,109,117;,
  3;118,119,62;,
  3;118,120,119;,
  3;118,121,120;,
  3;118,66,121;,
  3;118,122,66;,
  3;118,123,122;,
  3;118,124,123;,
  3;118,62,124;,
  4;62,119,126,125;,
  4;119,120,127,126;,
  4;120,121,128,127;,
  4;121,66,129,128;,
  4;66,122,130,129;,
  4;122,123,131,130;,
  4;123,124,132,131;,
  4;124,62,125,132;,
  4;125,126,134,133;,
  4;126,127,135,134;,
  4;127,128,136,135;,
  4;128,129,137,136;,
  4;129,130,138,137;,
  4;130,131,139,138;,
  4;131,132,85,139;,
  4;132,125,133,85;,
  4;133,134,141,140;,
  4;134,135,59,141;,
  4;135,136,142,59;,
  4;136,137,143,142;,
  4;137,138,144,143;,
  4;138,139,145,144;,
  4;139,85,32,145;,
  4;85,133,140,32;,
  4;140,141,147,146;,
  4;141,59,148,147;,
  4;59,142,149,148;,
  4;142,143,150,149;,
  4;143,144,151,150;,
  4;144,145,152,151;,
  4;145,32,100,152;,
  4;32,140,146,100;,
  4;146,147,154,153;,
  4;147,148,155,154;,
  4;148,149,156,155;,
  4;149,150,157,156;,
  4;150,151,158,157;,
  4;151,152,159,158;,
  4;152,100,160,159;,
  4;100,146,153,160;,
  4;153,154,162,161;,
  4;154,155,163,162;,
  4;155,156,164,163;,
  4;156,157,165,164;,
  4;157,158,166,165;,
  4;158,159,167,166;,
  4;159,160,168,167;,
  4;160,153,161,168;,
  3;161,162,169;,
  3;162,163,169;,
  3;163,164,169;,
  3;164,165,169;,
  3;165,166,169;,
  3;166,167,169;,
  3;167,168,169;,
  3;168,161,169;,
  3;170,171,171;,
  3;171,171,172;,
  3;172,173,173;,
  3;173,173,174;,
  3;174,175,175;,
  3;175,175,176;,
  3;176,177,177;,
  3;177,177,170;,
  3;178,178,178;,
  3;178,178,178;,
  3;178,178,178;,
  3;178,178,178;,
  3;178,178,178;,
  3;178,178,178;,
  3;178,178,178;,
  3;178,178,178;;
 }
 MeshTextureCoords {
  303;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
