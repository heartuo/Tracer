#include "bvh.h"

bool cmp_x(GeometricObject* p, GeometricObject* q)
{
	double px = p->get_centroid().x;
	double qx = q->get_centroid().x;

	return px < qx;
}

bool cmp_y(GeometricObject* p, GeometricObject* q)
{
	double py = p->get_centroid().y;
	double qy = q->get_centroid().y;

	return py < qy;
}

bool cmp_z(GeometricObject* p, GeometricObject* q)
{
	double pz = p->get_centroid().z;
	double qz = q->get_centroid().z;

	return pz < qz;
}

bool BVH::traverse(Ray ray, ShadeRec& sr, double& t, double& tmin, GeometricObject*& obj)
{
	Vector3D tmp = ray.o - c;
	double a = ray.d * ray.d;
	double b = 2.0 * tmp * ray.d;
	double cc = tmp * tmp - r * r;
	double disc = b * b - 4.0 * a * cc;

	if (disc < 0.0)
	{
		// cout << "hit nothing ..." << endl;
		return false;
	}
	else
	{
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (- b - e) / denom;

		if (t > kEpsilon)
		{
			// base case
			if (!prim.empty())
			{
				for (int j = 0; j < prim.size(); j++)
				{
					
					if (prim[j]->hit(ray, t, sr) && (t <= tmin))
					{
						obj = prim[j];
						tmin = t;
					}
				}
				//cout << "found obj" << endl;
				return true;
			}

			left->traverse(ray, sr, t, tmin, obj);
			right->traverse(ray, sr, t, tmin, obj);

			return true;
		}

		t = (- b + e) / denom;
		if (t > kEpsilon)
		{
			if (!prim.empty())
			{
				for (int j = 0; j < prim.size(); j++)
				{
					
					if (prim[j]->hit(ray, t, sr) && (t <= tmin))
					{
						obj = prim[j];
						tmin = t;
					}
				}
				// cout << "found obj" << endl;
				return true;
			}

			left->traverse(ray, sr, t, tmin, obj);
			right->traverse(ray, sr, t, tmin, obj);

			return true;
		}
	}

	//cout << "hit nothing ..." << endl;

	return false;
}

BVH::BVH()
{

}

BVH::BVH(std::vector<GeometricObject*> v)
{
	cout << "current node size: " << v.size() << endl;
	if (v.empty())
		return;

	// cout << "empty is " << prim.empty() << endl;	

	// get largest distances in dimensions

	GeometricObject* x_min = *(std::min_element(std::begin(v), std::end(v), cmp_x));
	GeometricObject* y_min = *(std::min_element(std::begin(v), std::end(v), cmp_y));
	GeometricObject* z_min = *(std::min_element(std::begin(v), std::end(v), cmp_z));

	GeometricObject* x_max = *(std::max_element(std::begin(v), std::end(v), cmp_x));
	GeometricObject* y_max = *(std::max_element(std::begin(v), std::end(v), cmp_y));
	GeometricObject* z_max = *(std::max_element(std::begin(v), std::end(v), cmp_z));

	Point3D px0 = x_min->get_centroid(), py0 = y_min->get_centroid(), pz0 = z_min->get_centroid();
	Point3D px1 = x_max->get_centroid(), py1 = y_max->get_centroid(), pz1 = z_max->get_centroid();

	// Vector3D rr(x_max.x - x_min.x + x_max.get_ext() + x_min.get_ext(), y_max.y - y_min.y + y_max.get_ext() + y_min.get_ext(), z_max.z - z_min.z + z_max.get_ext() + z_min.get_ext());

	Point3D c1(px1.x + x_max->get_ext(), py1.y + y_max->get_ext(), pz1.z + z_max->get_ext());
	Point3D c0(px0.x - x_min->get_ext(), py0.y - y_min->get_ext(), pz0.z - z_min->get_ext());

	Vector3D rr = (c1 - c0);

	r = rr.length() * 0.5;
	c = (c0 + c1) * 0.5;

	// cout << "r is " << r << endl;
	// cout << "c0 is " << "(" << c0.x << ", " << c0.y << ", " << c0.z << ") " << endl;
	// cout << "c1 is " << "(" << c1.x << ", " << c1.y << ", " << c1.z << ") " << endl;

	int axis = 0; // the longest axis
	// 0 is x
	// 1 is y
	// 2 is z

	if (rr.x > rr.y)
		axis = rr.x > rr.z?0 : 2;
	else
		axis = rr.y > rr.z?1 : 2;

	if (axis == 0)
		std::sort(v.begin(), v.end(), cmp_x);
	else if (axis == 1)
		std::sort(v.begin(), v.end(), cmp_y);
	else
		std::sort(v.begin(), v.end(), cmp_z);

	if (v.size() <= 3) // leaf determined with both object quantity and distance to others
	{
		prim = v;
		cout << "centroids: ";
		for (int i = 0; i < v.size(); i++)
		{
			cout << "(" << v[i]->get_centroid().x << ", " << v[i]->get_centroid().y << ", " << v[i]->get_centroid().z << ") ";
		}
		cout << endl;
		return;
	}

	left = new BVH(std::vector<GeometricObject*>(v.begin(), v.begin() + v.size() / 2));
	right = new BVH(std::vector<GeometricObject*>(v.begin() + v.size() / 2, v.end()));
}