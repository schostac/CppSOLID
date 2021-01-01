#include <iostream>
#include <vector>

/* Example of LSP violation.
 * Classes like https://docs.djangoproject.com/en/3.1/ref/models/querysets/
 */

template <typename Model>
class ORMQueryset {
public:
    virtual ~ORMQueryset() = default;
    virtual ORMQueryset& filterObjects(std::string, std::string) const = 0;
    virtual ORMQueryset& orderObjects(std::string, std::string) const = 0;
    virtual std::vector<Model> getObjects() const = 0;
    virtual unsigned updateObjects() = 0;
    virtual unsigned deleteObjects() = 0;
};

template <typename Model>
class Database1ORMQueryset : public ORMQueryset<Model> {
public:
    ORMQueryset<Model>& filterObjects(std::string, std::string) const override;
    ORMQueryset<Model>& orderObjects(std::string, std::string) const override;
    std::vector<Model> getObjects() const override;

    // OK, this type of databse informs us how many records were updated or deleted
    // upon the query and we return the value to the caller.
    unsigned updateObjects() override;
    unsigned deleteObjects() override;
};

template <typename Model>
class Database2ORMQueryset : public ORMQueryset<Model> {
public:
    ORMQueryset<Model>& filterObjects(std::string, std::string) const override;
    ORMQueryset<Model>& orderObjects(std::string, std::string) const override;
    std::vector<Model> getObjects() const override;

    // Now, for the sake of this example, image that this type of database
    // does not inform us about how many records were updated or deleted upon the query.
    // What should we do? Users might rely on the return value and use this class
    // via ORMQueryset base class not knowing about these details?
    // If we always returned 0, the postcondition would be broken as the return value may
    // be different from the number of just updated/deleted records.
    unsigned updateObjects() override;
    unsigned deleteObjects() override;
};

int main() {
}
