#include <Parabola.h>
#include <PrimitiveManager.h>

extern graphics::PrimitiveManager manager;

ParabolaSim::ParabolaSim() {

	x0[0] = glm::vec3(0.0f, 10.0f, 0.0f);
	x[0] = x0[0];

	x0[1] = glm::vec3(10.0f, 5.0f, 0.0f);
	x[1] = x0[1];

	v0[0] = glm::vec3(3.0f, 0.0f, 0.0f);
	v[0] = v0[0];

	v0[1] = glm::vec3(3.0f, 7.0f, 0.0f);
	v[1] = v0[1];

	a = glm::vec3(0.0f, -9.81f, 0.0f);

	particlesPrim = manager.NewParticles(2);
}

ParabolaSim::~ParabolaSim() {
	manager.DestroyPrimitive(particlesPrim);
}

void ParabolaSim::Update(float dt) {
	for (int i = 0; i < 2; i++)
	{
		glm::vec3 particle = EulerSolver(dt, i);
	}
}

void ParabolaSim::RenderUpdate() {
	particlesPrim->firstParticle = 0;
	particlesPrim->numParticles = 2;
	particlesPrim->Update(0, 2, &(x[0].x));
}

void ParabolaSim::RenderGui() {

}

glm::vec3 ParabolaSim::EulerSolver(float time, int iteration) {
	glm::vec3 auxPosition = x[iteration] + time * v[iteration];
	v[iteration] += time * a;
	if (x[iteration].y <= 0)
	{
		auxPosition = x0[iteration];
		v[iteration] = v0[iteration];
	}
	x[iteration] = auxPosition;
	return x[iteration];
}