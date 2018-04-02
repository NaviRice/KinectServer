import numpy as np
def generate_patch_location(image_shape, stride, kernel_size):
	x_rem = 20
	y_rem = 16
	width= image_shape[0]
	height= image_shape[1]
	X,Y = np.mgrid[-x_rem:width-x_rem:stride, -y_rem:height:stride]

	Xsort = sorted(set(X.flatten()))
	Ysort = sorted(set(Y.flatten()))

	Xdelt = []
	Ydelt = []
	for za, zb in zip(Xsort[1:], Xsort):
		Xdelt.append(za-zb)
	for za, zb in zip(Ysort[1:], Ysort):
		Ydelt.append(za-zb)

	print(Xsort)
	print(Xdelt)
	print(Ysort)
	print(Ydelt)


#	xy =np.vstack((X.flatten(), Y.flatten())).T
#	return xy
stackattack = generate_patch_location([424, 512], 16, 48)
#prettyprint(stackattack)
