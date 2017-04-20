#include "load_triangles_from_obj.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_PLUGIN(tomomesh) {
    py::module m("tomomesh", "loading meshes for tomographic projection");

    py::class_<Mesh, std::unique_ptr<Mesh, py::nodelete>>(m, "Mesh")
        .def(py::init<std::string>())
        .def("triangles", &Mesh::triangles)
        .def("bounding_box", &Mesh::bounding_box);

    return m.ptr();
}
