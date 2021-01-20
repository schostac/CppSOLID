#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
#include <cctype>

/* Storage example of LSP violation.
 * Classes inspired by https://docs.djangoproject.com/en/3.1/ref/files/storage/#django.core.files.storage.Storage
 * and https://django-storages.readthedocs.io/en/latest/backends/amazon-S3.html
 */

class String : public std::string {
public:
    using Base = std::string;
    using std::string::string;

    Base::size_type eraseSpaces(const int startFrom=0) {
        if (startFrom < 0 or startFrom > Base::size()) {
            throw std::logic_error{"Invalid start position"};
        }

        const auto oldSize = size();

        Base::erase(
            std::remove_if(
                Base::begin(),
                Base::end(), 
                [](const unsigned char c){ return std::isspace(c); }
            )
        );

        assert(Base::size() <= oldSize);

        // The following is redundant and rather job for tests
        assert(Base::find(' ', startFrom) == std::string::npos);
        assert(Base::find('\t', startFrom) == std::string::npos);
        std::cout << oldSize << std::endl;
        return oldSize - Base::size();
    }
};



int main() {
    auto s = String{"Text\n with\tsome \t  whitespaces\n"};
    std::cout << s.eraseSpaces() << std::endl;
    std::cout << s << std::endl;
}
