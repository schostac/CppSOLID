#include <memory>

/*
 * Example of LSP with covariant return types
 * and how compilers follow the principle.
 * This may be useful for factories, which should return specific
 * classes (sub-types) that they create.
 */

class Animal {
public:
    virtual ~Animal() = default;
};

class Tiger : public Animal {};
class Elephant : public Animal {};

class Zoo {
public:
    virtual ~Zoo() = default;
    virtual Animal* free() const = 0;
    // If we returned Tiger or other concrete (not building material :)) animal type,
    // that would be a too strong post-condition for other sub-classes,
    // what would they do? Cast? It'd thus be invalid covariant return type 
    // and that's why compilation would fail following LSP.
};

class TigerZoo : public Zoo {
public:
    Tiger* free() const override { return new Tiger; };
};

int main() {
    TigerZoo zoo;
    auto tiger = std::unique_ptr<Animal>{zoo.free()};
}
