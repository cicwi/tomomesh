import astra
import numpy as np
import tomomesh as tm


vectors = np.array([[600, 0, 0, 0, 100, -200, 0, 1, 0, 0, 0, 1],
                    [0, 100, -800, 0, 100, 0, 0, 1, 0, 1, 0, 0]],
                   dtype='float32')
proj_geom = astra.create_proj_geom('cone_vec', 600, 600, vectors)

mesh = tm.Mesh('data/clock_lowres.obj')
print(np.array(mesh.triangles()))
print(np.array(mesh.bounding_box()))

triangles = np.array(mesh.triangles(), dtype=np.float32)

tr_id = astra.ndarray.create(value=triangles)

proj_id = astra.data3d.create('-sino', proj_geom)

config = astra.astra_dict('TRIANGLE_MESH_FP')
config['ProjectionDataId'] = proj_id
config['TriangleMesh'] = tr_id
alg_id = astra.algorithm.create(config)
astra.algorithm.run(alg_id)

proj = astra.data3d.get(proj_id)

astra.algorithm.delete(alg_id)
astra.data3d.delete(proj_id)
astra.ndarray.delete(tr_id)

import pylab
pylab.gray()
pylab.imshow(proj[:, 0, :])
pylab.figure()
pylab.imshow(proj[:, 1, :])
pylab.show()
