#pragma once

#include <deal.II/grid/tria.h>
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/tria_iterator.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_out.h>
#include <deal.II/grid/manifold_lib.h>

#include <deal.II/dofs/dof_handler.h>
#include <deal.II/dofs/dof_tools.h>
#include <deal.II/dofs/dof_renumbering.h>

#include <deal.II/fe/fe_q.h>
#include <deal.II/fe/fe_dgq.h>

#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/dynamic_sparsity_pattern.h>

#include <iostream>
#include <fstream>
#include <cmath>

using namespace dealii;
using namespace std;

struct MyException : public std::exception
{
   std::string s;
   MyException(std::string ss) : s(ss) {}
   ~MyException() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};

void grid_generator(Triangulation<1>& triangulation, string grid_type);
void grid_generator(Triangulation<1, 2>& triangulation, string grid_type);
void grid_generator(Triangulation<2>& triangulation, string grid_type);
void grid_generator(Triangulation<2, 3>& triangulation, string grid_type);
void grid_generator(Triangulation<3>& triangulation, string grid_type);

template <int dim = 2, int spacedim = 2>
void save(Triangulation<dim, spacedim> &triangulation, string name)
{
    GridOut grid_out;

    ofstream out(name + ".vtk");
    grid_out.write_vtk(triangulation, out);
    out.close();
    
    cout << "grid written to \"" + name + ".vtk\"" << endl;
}

Triangulation<2> hyper_cube_grid(unsigned n_ref = 0);

Triangulation<2> hyper_cube_slit();

Triangulation<2> half_hyper_ball();

Triangulation<2> hyper_shell();

template <int dim = 2>
ostream& operator<<(ostream &out, const Triangulation<dim>& triangulation)
{   
    out << "Triangulation info" << endl;
    out << "dim: " << triangulation.dimension << endl;
    out << "n_active_cells: " << triangulation.n_active_cells() << endl;
    out << "n_active_faces: " << triangulation.n_active_faces() << endl;
    out << "n_active_lines: " << triangulation.n_active_lines() << endl;
    out << "n_active_quads: " << triangulation.n_active_quads() << endl;
    out << "n_global_active_cells: " << triangulation.n_global_active_cells() << endl;
    out << "n_global_levels: " << triangulation.n_global_levels() << endl;
    out << "n_levels: " << triangulation.n_levels() << endl;

    return out;
}

template <int dim = 2>
ostream& operator<<(ostream &out, const DoFHandler<dim>& dof_handler)
{
    cout << "DoF Handler info" << endl;
    cout << "number of dofs: " << dof_handler.n_dofs() << endl;
    cout << "number of boundary dofs: " << dof_handler.n_boundary_dofs() << endl;
    cout << "max connections: " << dof_handler.max_couplings_between_dofs() << endl;
    return out;
} 

SparsityPattern generate_sparsity_pattern(DoFHandler<2> &dof_handler);

enum renumberings 
{
    none,
    cuthill_McKee, 
    block_wise,
    clockwise_dg,
    hierarchical,
    random_renumbering,
    subdomain_wise
};

template <int dim = 2>
void distribute_dofs(
    Triangulation<dim> & triangulation, 
    renumberings renumbering_type = none, 
    int fe_degree = 1, 
    string file_name = "sparsity_pattern.svg")
{
    const FE_Q<dim> finite_element(fe_degree);
    DoFHandler<dim> dof_handler(triangulation);
    dof_handler.distribute_dofs(finite_element);
    cout << dof_handler;

    switch(renumbering_type)
    {
        case none:
            break;
        case cuthill_McKee:
            DoFRenumbering::Cuthill_McKee(dof_handler);
            break;
        case block_wise:
            DoFRenumbering::block_wise(dof_handler);
            break;
        case clockwise_dg:
            DoFRenumbering::clockwise_dg(dof_handler, Point<2>(0, 0));
            break;
        case hierarchical:
            DoFRenumbering::hierarchical(dof_handler);
            break;
        case random_renumbering:
            DoFRenumbering::random(dof_handler);
            break;
        case subdomain_wise:
            DoFRenumbering::subdomain_wise(dof_handler);
            break;
    }

    auto sparsity_pattern = generate_sparsity_pattern(dof_handler);
    dof_handler.clear();
        
    ofstream out(file_name);
    sparsity_pattern.print_svg(out);
    out.close();
}