#include <iostream>
#include <cassert>

/* Storage example of LSP violation.
 * Classes inspired by https://docs.djangoproject.com/en/3.1/ref/files/storage/#django.core.files.storage.Storage
 * and https://django-storages.readthedocs.io/en/latest/backends/amazon-S3.html
 * and https://docs.aws.amazon.com/code-samples/latest/catalog/code-catalog-cpp-example_code-s3.html
 */

class Storage {
public:
    virtual ~Storage() = default;
    virtual void open(std::string name) = 0;
    virtual void save(std::string name, std::string content) = 0;

    // "name" could be a directory path or file path, not restriction is made
    virtual void remove(std::string name) = 0;
};

class LocalFileStorage : public Storage {
public:
    void open(std::string name) override;
    void save(std::string name, std::string content) override;

    // OK, we use, for example, std::filesystem::remove to delete locally
    void remove(std::string name) override;
};

// Like DigitialOcean or AWS
class S3ObjectStorage : public Storage {
public:
    void open(std::string name) override;
    void save(std::string name, std::string content) override;

    // Now imagine, for the sake of this example, that S3 API takes only
    // path to an object, i.e. we can delete only file by file.
    // So if our user pass a path like "/files/media/images/users/1/",
    // what should we do?
    // Thus, the precondition is strengthened in subtype, which violates LSP. 
    void remove(std::string name) override
    {
        assert(not name.empty() and name.back() != '/');
        // Implementation omitted
    }
};

int main() {
}
