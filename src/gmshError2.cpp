#include <iostream>
#include <gmsh.h>
#include <vector>

class foo
{
public:
    int erroteste()
    {
        bool recombine_Q = true;
        for (int i = 0; i < 4; i++)
        {

            switch (i)
            {
                case 0:
                {

                    gmsh::initialize();

                    gmsh::model::geo::addPoint(0, 0, 0, 0., 1);
                    gmsh::model::geo::addPoint(1, 0, 0, 0., 2);
                    gmsh::model::geo::addPoint(0, 1, 0, 0., 4);
                    gmsh::model::geo::addPoint(1, 1, 0, 0., 5);
                    gmsh::model::geo::addPoint(0, 0, 1, 0., 10);
                    gmsh::model::geo::addPoint(1, 0, 1, 0., 11);
                    gmsh::model::geo::addPoint(0, 1, 1, 0., 13);
                    gmsh::model::geo::addPoint(1, 1, 1, 0., 14);
                    gmsh::model::geo::addPoint(0.5, 0.5, 0.5, 0., 19);
                    gmsh::model::geo::addPoint(1, 1, 0.5, 0., 23);
                    gmsh::model::geo::addPoint(0.5, 1, 0.5, 0., 24);
                    gmsh::model::geo::addPoint(1, 0.5, 0.5, 0., 25);
                    gmsh::model::geo::addPoint(0.75, 0.75, 0.5, 0., 28);

                    gmsh::model::geo::addLine(13, 10, 25);
                    gmsh::model::geo::mesh::setTransfiniteCurve(25, 2);
                    gmsh::model::geo::addLine(14, 13, 26);
                    gmsh::model::geo::mesh::setTransfiniteCurve(26, 2);
                    gmsh::model::geo::addLine(11, 14, 27);
                    gmsh::model::geo::mesh::setTransfiniteCurve(27, 2);
                    gmsh::model::geo::addLine(11, 10, 28);
                    gmsh::model::geo::mesh::setTransfiniteCurve(28, 2);
                    gmsh::model::geo::addLine(4, 13, 29);
                    gmsh::model::geo::mesh::setTransfiniteCurve(29, 2);
                    gmsh::model::geo::addLine(2, 11, 31);
                    gmsh::model::geo::mesh::setTransfiniteCurve(31, 2);
                    gmsh::model::geo::addLine(10, 1, 32);
                    gmsh::model::geo::mesh::setTransfiniteCurve(32, 2);
                    gmsh::model::geo::addLine(4, 1, 33);
                    gmsh::model::geo::mesh::setTransfiniteCurve(33, 2);
                    gmsh::model::geo::addLine(5, 4, 34);
                    gmsh::model::geo::mesh::setTransfiniteCurve(34, 2);
                    gmsh::model::geo::addLine(2, 5, 35);
                    gmsh::model::geo::mesh::setTransfiniteCurve(35, 2);
                    gmsh::model::geo::addLine(1, 2, 36);
                    gmsh::model::geo::mesh::setTransfiniteCurve(36, 2);
                    gmsh::model::geo::addLine(5, 23, 58);
                    gmsh::model::geo::mesh::setTransfiniteCurve(58, 2);
                    gmsh::model::geo::addLine(23, 14, 59);
                    gmsh::model::geo::mesh::setTransfiniteCurve(59, 2);
                    gmsh::model::geo::addLine(24, 23, 60);
                    gmsh::model::geo::mesh::setTransfiniteCurve(60, 2);
                    gmsh::model::geo::addLine(25, 23, 66);
                    gmsh::model::geo::mesh::setTransfiniteCurve(66, 2);
                    gmsh::model::geo::addLine(24, 14, 84);
                    gmsh::model::geo::mesh::setTransfiniteCurve(84, 2);
                    gmsh::model::geo::addLine(24, 13, 85);
                    gmsh::model::geo::mesh::setTransfiniteCurve(85, 2);
                    gmsh::model::geo::addLine(24, 4, 86);
                    gmsh::model::geo::mesh::setTransfiniteCurve(86, 2);
                    gmsh::model::geo::addLine(24, 5, 87);
                    gmsh::model::geo::mesh::setTransfiniteCurve(87, 2);
                    gmsh::model::geo::addLine(25, 14, 88);
                    gmsh::model::geo::mesh::setTransfiniteCurve(88, 2);
                    gmsh::model::geo::addLine(25, 11, 89);
                    gmsh::model::geo::mesh::setTransfiniteCurve(89, 2);
                    gmsh::model::geo::addLine(25, 2, 90);
                    gmsh::model::geo::mesh::setTransfiniteCurve(90, 2);
                    gmsh::model::geo::addLine(25, 5, 91);
                    gmsh::model::geo::mesh::setTransfiniteCurve(91, 2);
                    gmsh::model::geo::addLine(19, 25, 100);
                    gmsh::model::geo::mesh::setTransfiniteCurve(100, 2);
                    gmsh::model::geo::addLine(24, 19, 107);
                    gmsh::model::geo::mesh::setTransfiniteCurve(107, 2);
                    gmsh::model::geo::addLine(24, 28, 124);
                    gmsh::model::geo::mesh::setTransfiniteCurve(124, 2);
                    gmsh::model::geo::addLine(28, 19, 125);
                    gmsh::model::geo::mesh::setTransfiniteCurve(125, 2);
                    gmsh::model::geo::addLine(28, 25, 126);
                    gmsh::model::geo::mesh::setTransfiniteCurve(126, 2);
                    gmsh::model::geo::addLine(23, 28, 136);
                    gmsh::model::geo::mesh::setTransfiniteCurve(136, 2);

                    std::vector<int> wiretag(1);

                    wiretag[0] = gmsh::model::geo::addCurveLoop({-28, 27, 26, 25}, 5);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({-33, 29, 25, 32}, 6);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({60, 59, -84}, 61);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({84, 26, -85}, 62);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({85, -29, -86}, 63);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({86, -34, -87}, 64);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({87, 58, -60}, 65);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({66, 59, -88}, 67);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({88, -27, -89}, 68);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({89, -31, -90}, 69);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({90, 35, -91}, 70);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({91, 58, -66}, 71);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({36, 31, 28, 32}, 9);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({36, 35, 34, 33}, 10);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({107, -125, -124}, 108);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({100, -126, 125}, 109);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({-60, 124, -136}, 116);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({66, 136, 126}, 118);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);

                    std::vector<int> shelltag(1);

                    shelltag[0] = gmsh::model::geo::addSurfaceLoop({5, 6, 61, 62, 63, 64, 65, 67, 68, 69, 70, 71, 9, 10}, 1);
                    gmsh::model::geo::addVolume(shelltag, shelltag[0]);

                    gmsh::model::geo::synchronize();
                    gmsh::model::mesh::embed(2, {108, 109, 116, 118}, 3, 1);

                    gmsh::model::addPhysicalGroup(2, {108, 109, 116, 118}, 40);
                    gmsh::model::addPhysicalGroup(2, {5, 6, 61, 62, 63, 64, 65, 67, 68, 69, 70, 71, 9, 10}, 18);
                    gmsh::model::addPhysicalGroup(3, {1}, 18);

                    gmsh::model::geo::synchronize();
                    gmsh::model::mesh::generate(3);

                                        
                                        
                                        
                                        gmsh::write("test.msh");                    gmsh::write("test.msh");                    gmsh::write("test.msh");gmsh::write("test.msh");
                    gmsh::finalize();
                }

                case 1:
                {

                    gmsh::initialize();

                    gmsh::model::geo::addPoint(1, 0, 0, 0., 2);
                    gmsh::model::geo::addPoint(2, 0, 0, 0., 3);
                    gmsh::model::geo::addPoint(1, 1, 0, 0., 5);
                    gmsh::model::geo::addPoint(2, 1, 0, 0., 6);
                    gmsh::model::geo::addPoint(1, 0, 1, 0., 11);
                    gmsh::model::geo::addPoint(2, 0, 1, 0., 12);
                    gmsh::model::geo::addPoint(1, 1, 1, 0., 14);
                    gmsh::model::geo::addPoint(2, 1, 1, 0., 15);
                    gmsh::model::geo::addPoint(1.5, 0.5, 0.5, 0., 20);
                    gmsh::model::geo::addPoint(1, 1, 0.5, 0., 23);
                    gmsh::model::geo::addPoint(1, 0.5, 0.5, 0., 25);
                    gmsh::model::geo::addPoint(1.5, 1, 0.5, 0., 26);
                    gmsh::model::geo::addPoint(1.25, 0.75, 0.5, 0., 29);

                    gmsh::model::geo::addLine(11, 14, 27);
                    gmsh::model::geo::mesh::setTransfiniteCurve(27, 2);
                    gmsh::model::geo::addLine(2, 11, 31);
                    gmsh::model::geo::mesh::setTransfiniteCurve(31, 2);
                    gmsh::model::geo::addLine(2, 5, 35);
                    gmsh::model::geo::mesh::setTransfiniteCurve(35, 2);
                    gmsh::model::geo::addLine(15, 14, 37);
                    gmsh::model::geo::mesh::setTransfiniteCurve(37, 2);
                    gmsh::model::geo::addLine(15, 12, 38);
                    gmsh::model::geo::mesh::setTransfiniteCurve(38, 2);
                    gmsh::model::geo::addLine(12, 11, 39);
                    gmsh::model::geo::mesh::setTransfiniteCurve(39, 2);
                    gmsh::model::geo::addLine(6, 15, 40);
                    gmsh::model::geo::mesh::setTransfiniteCurve(40, 2);
                    gmsh::model::geo::addLine(3, 12, 41);
                    gmsh::model::geo::mesh::setTransfiniteCurve(41, 2);
                    gmsh::model::geo::addLine(6, 5, 42);
                    gmsh::model::geo::mesh::setTransfiniteCurve(42, 2);
                    gmsh::model::geo::addLine(3, 6, 43);
                    gmsh::model::geo::mesh::setTransfiniteCurve(43, 2);
                    gmsh::model::geo::addLine(2, 3, 44);
                    gmsh::model::geo::mesh::setTransfiniteCurve(44, 2);
                    gmsh::model::geo::addLine(5, 23, 58);
                    gmsh::model::geo::mesh::setTransfiniteCurve(58, 2);
                    gmsh::model::geo::addLine(23, 14, 59);
                    gmsh::model::geo::mesh::setTransfiniteCurve(59, 2);
                    gmsh::model::geo::addLine(25, 23, 66);
                    gmsh::model::geo::mesh::setTransfiniteCurve(66, 2);
                    gmsh::model::geo::addLine(26, 23, 72);
                    gmsh::model::geo::mesh::setTransfiniteCurve(72, 2);
                    gmsh::model::geo::addLine(25, 14, 88);
                    gmsh::model::geo::mesh::setTransfiniteCurve(88, 2);
                    gmsh::model::geo::addLine(25, 11, 89);
                    gmsh::model::geo::mesh::setTransfiniteCurve(89, 2);
                    gmsh::model::geo::addLine(25, 2, 90);
                    gmsh::model::geo::mesh::setTransfiniteCurve(90, 2);
                    gmsh::model::geo::addLine(25, 5, 91);
                    gmsh::model::geo::mesh::setTransfiniteCurve(91, 2);
                    gmsh::model::geo::addLine(26, 5, 92);
                    gmsh::model::geo::mesh::setTransfiniteCurve(92, 2);
                    gmsh::model::geo::addLine(26, 6, 93);
                    gmsh::model::geo::mesh::setTransfiniteCurve(93, 2);
                    gmsh::model::geo::addLine(26, 15, 94);
                    gmsh::model::geo::mesh::setTransfiniteCurve(94, 2);
                    gmsh::model::geo::addLine(26, 14, 95);
                    gmsh::model::geo::mesh::setTransfiniteCurve(95, 2);
                    gmsh::model::geo::addLine(25, 20, 101);
                    gmsh::model::geo::mesh::setTransfiniteCurve(101, 2);
                    gmsh::model::geo::addLine(20, 26, 102);
                    gmsh::model::geo::mesh::setTransfiniteCurve(102, 2);
                    gmsh::model::geo::addLine(25, 29, 127);
                    gmsh::model::geo::mesh::setTransfiniteCurve(127, 2);
                    gmsh::model::geo::addLine(29, 20, 128);
                    gmsh::model::geo::mesh::setTransfiniteCurve(128, 2);
                    gmsh::model::geo::addLine(29, 26, 129);
                    gmsh::model::geo::mesh::setTransfiniteCurve(129, 2);
                    gmsh::model::geo::addLine(23, 29, 138);
                    gmsh::model::geo::mesh::setTransfiniteCurve(138, 2);

                    std::vector<int> wiretag(1);

                    wiretag[0] = gmsh::model::geo::addCurveLoop({-39, -38, 37, -27}, 11);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({66, 59, -88}, 67);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({88, -27, -89}, 68);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({89, -31, -90}, 69);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({90, 35, -91}, 70);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({91, 58, -66}, 71);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({72, -58, -92}, 73);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({92, -42, -93}, 74);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({93, 40, -94}, 75);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({94, 37, -95}, 76);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({95, -59, -72}, 77);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({43, 40, 38, -41}, 13);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({44, 41, 39, -31}, 14);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({44, 43, 42, -35}, 15);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({101, -128, -127}, 110);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({102, -129, 128}, 111);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({-66, 127, -138}, 119);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({72, 138, 129}, 120);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);

                    std::vector<int> shelltag(1);

                    shelltag[0] = gmsh::model::geo::addSurfaceLoop({11, 67, 68, 69, 70, 71, 73, 74, 75, 76, 77, 13, 14, 15}, 2);
                    gmsh::model::geo::addVolume(shelltag, shelltag[0]);

                    gmsh::model::geo::synchronize();
                    gmsh::model::mesh::embed(2, {110, 111, 119, 120}, 3, 2);

                    gmsh::model::addPhysicalGroup(2, {110, 111, 119, 120}, 40);
                    gmsh::model::addPhysicalGroup(2, {11, 67, 68, 69, 70, 71, 73, 74, 75, 76, 77, 13, 14, 15}, 18);
                    gmsh::model::addPhysicalGroup(3, {2}, 18);

                    gmsh::model::geo::synchronize();
                    gmsh::model::mesh::generate(3);
                    
                                        
                                        
                                        gmsh::write("test.msh");                    gmsh::write("test.msh");gmsh::write("test.msh");
                    gmsh::finalize();
                }

                case 2:
                {

                    gmsh::initialize();

                    gmsh::model::geo::addPoint(0, 1, 0, 0., 4);
                    gmsh::model::geo::addPoint(1, 1, 0, 0., 5);
                    gmsh::model::geo::addPoint(0, 2, 0, 0., 7);
                    gmsh::model::geo::addPoint(1, 2, 0, 0., 8);
                    gmsh::model::geo::addPoint(0, 1, 1, 0., 13);
                    gmsh::model::geo::addPoint(1, 1, 1, 0., 14);
                    gmsh::model::geo::addPoint(0, 2, 1, 0., 16);
                    gmsh::model::geo::addPoint(1, 2, 1, 0., 17);
                    gmsh::model::geo::addPoint(0.5, 1.5, 0.5, 0., 22);
                    gmsh::model::geo::addPoint(1, 1, 0.5, 0., 23);
                    gmsh::model::geo::addPoint(0.5, 1, 0.5, 0., 24);
                    gmsh::model::geo::addPoint(1, 1.5, 0.5, 0., 27);
                    gmsh::model::geo::addPoint(0.75, 1.25, 0.5, 0., 31);

                    gmsh::model::geo::addLine(14, 13, 26);
                    gmsh::model::geo::mesh::setTransfiniteCurve(26, 2);
                    gmsh::model::geo::addLine(4, 13, 29);
                    gmsh::model::geo::mesh::setTransfiniteCurve(29, 2);
                    gmsh::model::geo::addLine(5, 4, 34);
                    gmsh::model::geo::mesh::setTransfiniteCurve(34, 2);
                    gmsh::model::geo::addLine(16, 13, 45);
                    gmsh::model::geo::mesh::setTransfiniteCurve(45, 2);
                    gmsh::model::geo::addLine(17, 16, 46);
                    gmsh::model::geo::mesh::setTransfiniteCurve(46, 2);
                    gmsh::model::geo::addLine(14, 17, 47);
                    gmsh::model::geo::mesh::setTransfiniteCurve(47, 2);
                    gmsh::model::geo::addLine(16, 7, 48);
                    gmsh::model::geo::mesh::setTransfiniteCurve(48, 2);
                    gmsh::model::geo::addLine(8, 17, 49);
                    gmsh::model::geo::mesh::setTransfiniteCurve(49, 2);
                    gmsh::model::geo::addLine(7, 4, 50);
                    gmsh::model::geo::mesh::setTransfiniteCurve(50, 2);
                    gmsh::model::geo::addLine(8, 7, 51);
                    gmsh::model::geo::mesh::setTransfiniteCurve(51, 2);
                    gmsh::model::geo::addLine(5, 8, 52);
                    gmsh::model::geo::mesh::setTransfiniteCurve(52, 2);
                    gmsh::model::geo::addLine(5, 23, 58);
                    gmsh::model::geo::mesh::setTransfiniteCurve(58, 2);
                    gmsh::model::geo::addLine(23, 14, 59);
                    gmsh::model::geo::mesh::setTransfiniteCurve(59, 2);
                    gmsh::model::geo::addLine(24, 23, 60);
                    gmsh::model::geo::mesh::setTransfiniteCurve(60, 2);
                    gmsh::model::geo::addLine(27, 23, 78);
                    gmsh::model::geo::mesh::setTransfiniteCurve(78, 2);
                    gmsh::model::geo::addLine(24, 14, 84);
                    gmsh::model::geo::mesh::setTransfiniteCurve(84, 2);
                    gmsh::model::geo::addLine(24, 13, 85);
                    gmsh::model::geo::mesh::setTransfiniteCurve(85, 2);
                    gmsh::model::geo::addLine(24, 4, 86);
                    gmsh::model::geo::mesh::setTransfiniteCurve(86, 2);
                    gmsh::model::geo::addLine(24, 5, 87);
                    gmsh::model::geo::mesh::setTransfiniteCurve(87, 2);
                    gmsh::model::geo::addLine(27, 5, 96);
                    gmsh::model::geo::mesh::setTransfiniteCurve(96, 2);
                    gmsh::model::geo::addLine(27, 8, 97);
                    gmsh::model::geo::mesh::setTransfiniteCurve(97, 2);
                    gmsh::model::geo::addLine(27, 17, 98);
                    gmsh::model::geo::mesh::setTransfiniteCurve(98, 2);
                    gmsh::model::geo::addLine(27, 14, 99);
                    gmsh::model::geo::mesh::setTransfiniteCurve(99, 2);
                    gmsh::model::geo::addLine(27, 22, 105);
                    gmsh::model::geo::mesh::setTransfiniteCurve(105, 2);
                    gmsh::model::geo::addLine(22, 24, 106);
                    gmsh::model::geo::mesh::setTransfiniteCurve(106, 2);
                    gmsh::model::geo::addLine(22, 31, 133);
                    gmsh::model::geo::mesh::setTransfiniteCurve(133, 2);
                    gmsh::model::geo::addLine(31, 24, 134);
                    gmsh::model::geo::mesh::setTransfiniteCurve(134, 2);
                    gmsh::model::geo::addLine(27, 31, 135);
                    gmsh::model::geo::mesh::setTransfiniteCurve(135, 2);
                    gmsh::model::geo::addLine(31, 23, 137);
                    gmsh::model::geo::mesh::setTransfiniteCurve(137, 2);

                    std::vector<int> wiretag(1);

                    wiretag[0] = gmsh::model::geo::addCurveLoop({-26, 47, 46, 45}, 16);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({-50, -48, 45, -29}, 17);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({-51, 49, 46, 48}, 18);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({78, -58, -96}, 79);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({96, 52, -97}, 80);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({97, 49, -98}, 81);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({98, -47, -99}, 82);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({99, -59, -78}, 83);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({60, 59, -84}, 61);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({84, 26, -85}, 62);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({85, -29, -86}, 63);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({86, -34, -87}, 64);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({87, 58, -60}, 65);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({-34, 52, 51, 50}, 20);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({106, -134, -133}, 114);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({105, 133, -135}, 115);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({60, -137, 134}, 117);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({-78, 135, 137}, 123);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);

                    std::vector<int> shelltag(1);

                    shelltag[0] = gmsh::model::geo::addSurfaceLoop({16, 17, 18, 79, 80, 81, 82, 83, 61, 62, 63, 64, 65, 20}, 3);
                    gmsh::model::geo::addVolume(shelltag, shelltag[0]);

                    gmsh::model::geo::synchronize();
                    gmsh::model::mesh::embed(2, {114, 115, 117, 123}, 3, 3);

                    gmsh::model::addPhysicalGroup(2, {114, 115, 117, 123}, 40);
                    gmsh::model::addPhysicalGroup(2, {16, 17, 18, 79, 80, 81, 82, 83, 61, 62, 63, 64, 65, 20}, 18);
                    gmsh::model::addPhysicalGroup(3, {3}, 18);

                    gmsh::model::geo::synchronize();
                    gmsh::model::mesh::generate(3);

                                        
                                        gmsh::write("test.msh");gmsh::write("test.msh");
                    gmsh::finalize();
                }

                case 3:
                {

                    gmsh::initialize();

                    gmsh::model::geo::addPoint(1, 1, 0, 0., 5);
                    gmsh::model::geo::addPoint(2, 1, 0, 0., 6);
                    gmsh::model::geo::addPoint(1, 2, 0, 0., 8);
                    gmsh::model::geo::addPoint(2, 2, 0, 0., 9);
                    gmsh::model::geo::addPoint(1, 1, 1, 0., 14);
                    gmsh::model::geo::addPoint(2, 1, 1, 0., 15);
                    gmsh::model::geo::addPoint(1, 2, 1, 0., 17);
                    gmsh::model::geo::addPoint(2, 2, 1, 0., 18);
                    gmsh::model::geo::addPoint(1.5, 1.5, 0.5, 0., 21);
                    gmsh::model::geo::addPoint(1, 1, 0.5, 0., 23);
                    gmsh::model::geo::addPoint(1.5, 1, 0.5, 0., 26);
                    gmsh::model::geo::addPoint(1, 1.5, 0.5, 0., 27);
                    gmsh::model::geo::addPoint(1.25, 1.25, 0.5, 0., 30);

                    gmsh::model::geo::addLine(15, 14, 37);
                    gmsh::model::geo::mesh::setTransfiniteCurve(37, 2);
                    gmsh::model::geo::addLine(6, 15, 40);
                    gmsh::model::geo::mesh::setTransfiniteCurve(40, 2);
                    gmsh::model::geo::addLine(6, 5, 42);
                    gmsh::model::geo::mesh::setTransfiniteCurve(42, 2);
                    gmsh::model::geo::addLine(14, 17, 47);
                    gmsh::model::geo::mesh::setTransfiniteCurve(47, 2);
                    gmsh::model::geo::addLine(8, 17, 49);
                    gmsh::model::geo::mesh::setTransfiniteCurve(49, 2);
                    gmsh::model::geo::addLine(5, 8, 52);
                    gmsh::model::geo::mesh::setTransfiniteCurve(52, 2);
                    gmsh::model::geo::addLine(18, 17, 53);
                    gmsh::model::geo::mesh::setTransfiniteCurve(53, 2);
                    gmsh::model::geo::addLine(18, 15, 54);
                    gmsh::model::geo::mesh::setTransfiniteCurve(54, 2);
                    gmsh::model::geo::addLine(9, 18, 55);
                    gmsh::model::geo::mesh::setTransfiniteCurve(55, 2);
                    gmsh::model::geo::addLine(9, 8, 56);
                    gmsh::model::geo::mesh::setTransfiniteCurve(56, 2);
                    gmsh::model::geo::addLine(6, 9, 57);
                    gmsh::model::geo::mesh::setTransfiniteCurve(57, 2);
                    gmsh::model::geo::addLine(5, 23, 58);
                    gmsh::model::geo::mesh::setTransfiniteCurve(58, 2);
                    gmsh::model::geo::addLine(23, 14, 59);
                    gmsh::model::geo::mesh::setTransfiniteCurve(59, 2);
                    gmsh::model::geo::addLine(26, 23, 72);
                    gmsh::model::geo::mesh::setTransfiniteCurve(72, 2);
                    gmsh::model::geo::addLine(27, 23, 78);
                    gmsh::model::geo::mesh::setTransfiniteCurve(78, 2);
                    gmsh::model::geo::addLine(26, 5, 92);
                    gmsh::model::geo::mesh::setTransfiniteCurve(92, 2);
                    gmsh::model::geo::addLine(26, 6, 93);
                    gmsh::model::geo::mesh::setTransfiniteCurve(93, 2);
                    gmsh::model::geo::addLine(26, 15, 94);
                    gmsh::model::geo::mesh::setTransfiniteCurve(94, 2);
                    gmsh::model::geo::addLine(26, 14, 95);
                    gmsh::model::geo::mesh::setTransfiniteCurve(95, 2);
                    gmsh::model::geo::addLine(27, 5, 96);
                    gmsh::model::geo::mesh::setTransfiniteCurve(96, 2);
                    gmsh::model::geo::addLine(27, 8, 97);
                    gmsh::model::geo::mesh::setTransfiniteCurve(97, 2);
                    gmsh::model::geo::addLine(27, 17, 98);
                    gmsh::model::geo::mesh::setTransfiniteCurve(98, 2);
                    gmsh::model::geo::addLine(27, 14, 99);
                    gmsh::model::geo::mesh::setTransfiniteCurve(99, 2);
                    gmsh::model::geo::addLine(26, 21, 103);
                    gmsh::model::geo::mesh::setTransfiniteCurve(103, 2);
                    gmsh::model::geo::addLine(21, 27, 104);
                    gmsh::model::geo::mesh::setTransfiniteCurve(104, 2);
                    gmsh::model::geo::addLine(26, 30, 130);
                    gmsh::model::geo::mesh::setTransfiniteCurve(130, 2);
                    gmsh::model::geo::addLine(30, 21, 131);
                    gmsh::model::geo::mesh::setTransfiniteCurve(131, 2);
                    gmsh::model::geo::addLine(30, 27, 132);
                    gmsh::model::geo::mesh::setTransfiniteCurve(132, 2);
                    gmsh::model::geo::addLine(23, 30, 139);
                    gmsh::model::geo::mesh::setTransfiniteCurve(139, 2);

                    std::vector<int> wiretag(1);

                    wiretag[0] = gmsh::model::geo::addCurveLoop({-37, -54, 53, -47}, 21);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({78, -58, -96}, 79);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({96, 52, -97}, 80);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({97, 49, -98}, 81);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({98, -47, -99}, 82);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({99, -59, -78}, 83);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({-56, 55, 53, -49}, 22);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({57, 55, 54, -40}, 23);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({72, -58, -92}, 73);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({92, -42, -93}, 74);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({93, 40, -94}, 75);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({94, 37, -95}, 76);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({95, -59, -72}, 77);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({-42, 57, 56, -52}, 24);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({103, -131, -130}, 112);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({104, -132, 131}, 113);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({-72, 130, -139}, 121);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);
                    wiretag[0] = gmsh::model::geo::addCurveLoop({78, 139, 132}, 122);
                    gmsh::model::geo::addSurfaceFilling(wiretag, wiretag[0]);
                    gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
                    if (recombine_Q)
                        gmsh::model::geo::mesh::setRecombine(2, wiretag[0]);

                    std::vector<int> shelltag(1);

                    shelltag[0] = gmsh::model::geo::addSurfaceLoop({21, 79, 80, 81, 82, 83, 22, 23, 73, 74, 75, 76, 77, 24}, 4);
                    gmsh::model::geo::addVolume(shelltag, shelltag[0]);

                    gmsh::model::geo::synchronize();
                    gmsh::model::mesh::embed(2, {112, 113, 121, 122}, 3, 4);

                    gmsh::model::addPhysicalGroup(2, {112, 113, 121, 122}, 40);
                    gmsh::model::addPhysicalGroup(2, {21, 79, 80, 81, 82, 83, 22, 23, 73, 74, 75, 76, 77, 24}, 18);
                    gmsh::model::addPhysicalGroup(3, {4}, 18);

                    gmsh::model::geo::synchronize();
                    gmsh::model::mesh::generate(3);

                    gmsh::write("test.msh");
                    gmsh::finalize();
                }
            }
        }
        return 0;
    }
};