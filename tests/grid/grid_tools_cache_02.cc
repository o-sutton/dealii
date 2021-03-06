// ---------------------------------------------------------------------
//
// Copyright (C) 2001 - 2017 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------

// Validate grid_tools_cache. Different construction order. Check signal.

#include "../tests.h"
#include <deal.II/grid/tria.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools_cache.h>


template <int dim, int spacedim>
void test ()
{
  deallog << "dim = " << dim
          << ", spacedim = " << spacedim << std::endl;

  Triangulation<dim> tria;
  GridTools::Cache<dim> cache(tria);

  GridGenerator::hyper_cube(tria);

  {
    auto m = cache.get_vertex_to_cell_map();

    unsigned int i=0;
    for (auto &v : m)
      {
        for (auto &c : v)
          deallog << "Vertex " << i << ", cell " << c << std::endl;
        ++i;
      }
  }
  deallog << "After one refinement. " << std::endl;

  tria.refine_global(1);
  {
    auto m = cache.get_vertex_to_cell_map();

    unsigned int i=0;
    for (auto &v : m)
      {
        for (auto &c : v)
          deallog << "Vertex " << i << ", cell " << c << std::endl;
        ++i;
      }
  }
}


int main ()
{
  initlog();

  test<2,2> ();

  return 0;
}
