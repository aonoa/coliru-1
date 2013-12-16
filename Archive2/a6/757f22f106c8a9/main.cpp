#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/bimap.hpp>
#include <cstdlib>

namespace qi    = boost::spirit::qi;

struct Student
{
    int i;
    std::string s;

    bool operator<(Student const& other) const {
        return boost::tie(i,s) < boost::tie(other.i, other.s);
    }
    friend std::ostream& operator<<(std::ostream& os, Student const& o) {
        return os << "Student - [int " << o.i << "][string " << o.s << "]";
    }
};

struct Roster
{
    std::vector<Student> students;
};

BOOST_FUSION_ADAPT_STRUCT(Student, (int, i)(std::string, s))
BOOST_FUSION_ADAPT_STRUCT(Roster, (std::vector<Student>, students))

typedef std::vector<Roster> ParsedT3Data;

template <typename Iterator>
struct roster_grammar : qi::grammar<Iterator, ParsedT3Data(), qi::blank_type>
{   
    roster_grammar() : 
        roster_grammar::base_type(start)
    {
        using namespace qi;

        start   = roster %  eol;
        roster  = eps    >> +student; // known workaround
        student = int_   >> string_p;

        string_p = lexeme[+(graph)];

        BOOST_SPIRIT_DEBUG_NODES((start)(roster)(student)(string_p))
    }

    qi::rule <Iterator, ParsedT3Data(), qi::blank_type> start;
    qi::rule <Iterator, Roster(),       qi::blank_type> roster;
    qi::rule <Iterator, Student(),      qi::blank_type> student;
    qi::rule <Iterator, std::string()>  string_p;
};

ParsedT3Data parseData(std::string const& demoData)
{
    typedef boost::spirit::istream_iterator iter_type;
    roster_grammar<iter_type> my_parser;

    //open the target file and wrap istream into the iterator
    std::istringstream iss(demoData);
    iss.unsetf(std::ios::skipws); //Disable Whitespace Skipping

    iter_type begin(iss), end;
    ParsedT3Data result;
    bool r = phrase_parse(begin, end, my_parser, qi::blank, result);

    if (r)
        std::cout << "parse (partial) success\n";
    else      
        std::cerr << "parse failed: '" << std::string(begin,end) << "'\n";
    if (begin!=end) 
        std::cerr << "trailing unparsed: '" << std::string(begin,end) << "'\n";

    if (!r) 
        throw "TODO error handling";

    return result;
}

int main()
{
    ParsedT3Data const data = parseData(
            "23 Bryan 45 Tyler 4 Stephen\n"
            "7 Mary 45 Tyler 8 Stephane\n"
            "23 Bryan 8 Stephane");

    // now produce that list of stuff :)
    std::map<std::string, Student> student_by_var;
    std::map<Student, std::string> var_by_student;

    int id = 1;
    for(ParsedT3Data::const_iterator rit = data.begin(); rit != data.end(); ++rit)
        for(std::vector<Student>::const_iterator sit = rit->students.begin(); sit != rit->students.end(); ++sit)
        {
            if (var_by_student.find(*sit) == var_by_student.end())
            {
                char varname[20];
                snprintf(varname, 20, "s%d", id++);
                student_by_var.insert(std::make_pair(varname, *sit));
                var_by_student.insert(std::make_pair(*sit, varname));
            }
        }

    for(std::map<std::string, Student>::const_iterator it = student_by_var.begin(); it!=student_by_var.end(); ++it)
        std::cout << it->first << " - " << it->second << "\n";

    id = 1;
    for(ParsedT3Data::const_iterator rit = data.begin(); rit != data.end(); ++rit)
    {
        std::cout << "r" << (id++) << " ";
        for(std::vector<Student>::const_iterator sit = rit->students.begin(); sit != rit->students.end(); ++sit)
            std::cout << "[" << var_by_student.at(*sit) << "]";
        std::cout << "\n";
    }
}
