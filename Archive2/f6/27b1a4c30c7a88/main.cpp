$ curl -nv 'stacked-crooked.com/log?count=1000000&grep=cppreference' 2>/dev/null | grep http | perl -pe 's,^.*?(http.*?)\s.*,\1,' | sort  | uniq -c | sort -r -n
  72 http://en.cppreference.com/w/cpp/language/auto
  54 http://en.cppreference.com/w/cpp/utility/tuple
  32 http://en.cppreference.com/w/cpp/container/array
  31 http://en.cppreference.com/w/cpp/utility/functional/function
  27 http://en.cppreference.com/w/cpp/string/wide/towupper
  27 http://en.cppreference.com/w/cpp/algorithm/accumulate
  25 http://en.cppreference.com/w/cpp/thread/yield
  23 http://en.cppreference.com/w/cpp/locale/codecvt
  22 http://en.cppreference.com/w/cpp/thread/sleep_for
  22 http://en.cppreference.com/w/cpp/thread/condition_variable
  21 http://en.cppreference.com/w/cpp/memory/unique_ptr
  19 http://en.cppreference.com/w/cpp/thread/async
  17 http://en.cppreference.com/w/cpp/types/enable_if
  17 http://en.cppreference.com/w/cpp/thread/call_once
  16 http://en.cppreference.com/w/cpp/language/user_literal
  16 http://en.cppreference.com/w/cpp/algorithm/equal_range
  15 http://en.cppreference.com/w/cpp/thread/future
  13 http://en.cppreference.com/w/cpp/types/size_t
  13 http://en.cppreference.com/w/cpp/numeric/random/srand
  13 http://en.cppreference.com/w/cpp/language/operator_alternative
  12 http://en.cppreference.com/w/cpp/utility/functional/mem_fn
  12 http://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared
  12 http://en.cppreference.com/w/cpp/algorithm/lower_bound
  12 http://en.cppreference.com/w/
  11 http://en.cppreference.com/w/cpp/utility/hash
  11 http://en.cppreference.com/w/cpp/utility/functional/bind
  11 http://en.cppreference.com/w/cpp/io/basic_istream/ignore
  11 http://en.cppreference.com/w/cpp/container/unordered_map/unordered_map
  10 http://en.cppreference.com/w/cpp/language/move_operator
  10 http://en.cppreference.com/w/cpp/io/basic_istream/getline
  10 http://en.cppreference.com/w/cpp/chrono/time_point
  10 http://en.cppreference.com/w/cpp/atomic/memory_order
  10 http://en.cppreference.com/w/cpp/algorithm/unique
  10 http://en.cppreference.com/w/cpp/algorithm/rotate
  10 http://en.cppreference.com/w/c/memory/free
   9 http://en.cppreference.com/w/cpp/utility/pair/make_pair
   9 http://en.cppreference.com/w/cpp/language/escape
   8 http://en.cppreference.com/w/cpp/string/basic_string/to_string
   8 http://en.cppreference.com/w/cpp/regex/regex_search
   8 http://en.cppreference.com/w/cpp/numeric/math/cbrt
   8 http://en.cppreference.com/w/cpp/keyword/and
   8 http://en.cppreference.com/w/cpp/io/c/fprintf
   8 http://en.cppreference.com/w/cpp/container/vector/vector
   8 http://en.cppreference.com/w/cpp/container/list/size
   8 http://en.cppreference.com/w/cpp/chrono/c/strftime
   8 http://en.cppreference.com/w/cpp/algorithm/remove_copy
   8 http://en.cppreference.com/w/c/io/fprintf
   7 http://en.cppreference.com/w/cpp/numeric/random/discrete_distribution
   7 http://en.cppreference.com/w/cpp/language/storage_duration
   7 http://en.cppreference.com/w/cpp/language/sizeof
   7 http://en.cppreference.com/w/cpp/language/move_constructor
   7 http://en.cppreference.com/w/cpp/iterator/distance
   7 http://en.cppreference.com/w/cpp/io/basic_istream/peek
   7 http://en.cppreference.com/w/cpp/error/uncaught_exception
   7 http://en.cppreference.com/w/cpp/error/nested_exception
   7 http://en.cppreference.com/w/cpp/chrono/c/time
   7 http://en.cppreference.com/w/cpp/chrono
   7 http://en.cppreference.com/w/cpp/algorithm/search
   6 http://en.cppreference.com/w/cpp/utility/program/getenv
   6 http://en.cppreference.com/w/cpp/thread/mutex
   6 http://en.cppreference.com/w/cpp/string/byte/atoi
   6 http://en.cppreference.com/w/cpp/string/basic_string/stol
   6 http://en.cppreference.com/w/cpp/memory/weak_ptr/lock
   6 http://en.cppreference.com/w/cpp/language/switch
   6 http://en.cppreference.com/w/cpp/container/vector/operator_at
   6 http://en.cppreference.com/w/cpp/atomic/atomic_compare_exchange
   5 http://en.cppreference.com/w/cpp/thread/mutex/try_lock
   5 http://en.cppreference.com/w/cpp/string/byte/strstr
   5 http://en.cppreference.com/w/cpp/string/basic_string/to_wstring
   5 http://en.cppreference.com/w/cpp/string/basic_string/getline
   5 http://en.cppreference.com/w/cpp/memory/allocator
   5 http://en.cppreference.com/w/cpp/language/range-for
   5 http://en.cppreference.com/w/cpp/language/operator_arithmetic
   5 http://en.cppreference.com/w/cpp/language/integer_literal
   5 http://en.cppreference.com/w/cpp/language/as_if
   5 http://en.cppreference.com/w/cpp/io/manip/showpoint
   5 http://en.cppreference.com/w/cpp/io/manip/boolalpha
   5 http://en.cppreference.com/w/cpp/io/basic_istream/read
   5 http://en.cppreference.com/w/cpp/container/vector/emplace_back
   5 http://en.cppreference.com/w/cpp/container/map/emplace
   5 http://en.cppreference.com/w/cpp/container/array/operator_at
   5 http://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch
   5 http://en.cppreference.com/w/cpp/algorithm/reverse_copy
   5 http://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
   5 http://en.cppreference.com/w/c/string/byte/strchr
   5 http://en.cppreference.com/mwiki/index.php?title=cpp/types/decay&action=submit
   4 http://en.cppreference.com/w/cpp/utility/variadic/va_copy
   4 http://en.cppreference.com/w/cpp/utility/move
   4 http://en.cppreference.com/w/cpp/utility/integer_sequence
   4 http://en.cppreference.com/w/cpp/string/basic_string/operator%22%22s
   4 http://en.cppreference.com/w/cpp/memory/unique_ptr/operator%3D
   4 http://en.cppreference.com/w/cpp/language/explicit
   4 http://en.cppreference.com/w/cpp/language/copy_elision
   4 http://en.cppreference.com/w/cpp/container/vector/push_back
   4 http://en.cppreference.com/w/cpp/container/list/sort
   4 http://en.cppreference.com/w/cpp/container/list/push_back
   4 http://en.cppreference.com/w/cpp/algorithm/max_element
   4 http://en.cppreference.com/w/cpp/algorithm/copy
   4 http://en.cppreference.com/w/c/string/byte/strrchr
   4 http://en.cppreference.com/w/c/string/byte/strpbrk
   4 http://en.cppreference.com/w/c/string/byte/strcmp
   3 http://en.cppreference.com/w/cpp/utility/tuple/tie
   3 http://en.cppreference.com/w/cpp/utility/tuple/make_tuple
   3 http://en.cppreference.com/w/cpp/utility/functional/binary_function
   3 http://en.cppreference.com/w/cpp/types/is_class
   3 http://en.cppreference.com/w/cpp/thread/shared_future
   3 http://en.cppreference.com/w/cpp/thread/condition_variable/notify_all
   3 http://en.cppreference.com/w/cpp/string/multibyte/wcstombs
   3 http://en.cppreference.com/w/cpp/string/byte/isalnum
   3 http://en.cppreference.com/w/cpp/regex
   3 http://en.cppreference.com/w/cpp/numeric/random/normal_distribution
   3 http://en.cppreference.com/w/cpp/numeric/random/exponential_distribution
   3 http://en.cppreference.com/w/cpp/numeric/fenv/feround
   3 http://en.cppreference.com/w/cpp/memory/align
   3 http://en.cppreference.com/w/cpp/language/string_literal
   3 http://en.cppreference.com/w/cpp/language/function
   3 http://en.cppreference.com/w/cpp/io/basic_ostream/tellp
   3 http://en.cppreference.com/w/cpp/error/assert
   3 http://en.cppreference.com/w/cpp/container/vector/back
   3 http://en.cppreference.com/w/cpp/container/stack/top
   3 http://en.cppreference.com/w/cpp/container/dynarray/back
   3 http://en.cppreference.com/w/cpp/atomic/atomic/compare_exchange
   3 http://en.cppreference.com/w/c/string/byte/strerror
   3 http://en.cppreference.com/w/c/string/byte/memcpy
   2 http://en.cppreference.com/w/cpp/utility/variadic/va_start
   2 http://en.cppreference.com/w/cpp/utility/program/system
   2 http://en.cppreference.com/w/cpp/utility/initializer_list
   2 http://en.cppreference.com/w/cpp/utility/functional/reference_wrapper
   2 http://en.cppreference.com/w/cpp/utility/forward
   2 http://en.cppreference.com/w/cpp/utility/bitset/operator_ltltgtgt2
   2 http://en.cppreference.com/w/cpp/types/remove_reference
   2 http://en.cppreference.com/w/cpp/types/numeric_limits/max
   2 http://en.cppreference.com/w/cpp/types/max_align_t
   2 http://en.cppreference.com/w/cpp/types/is_trivially_copyable
   2 http://en.cppreference.com/w/cpp/types/conditional
   2 http://en.cppreference.com/w/cpp/thread/unique_lock
   2 http://en.cppreference.com/w/cpp/thread/try_lock
   2 http://en.cppreference.com/w/cpp/thread/thread/thread
   2 http://en.cppreference.com/w/cpp/thread/thread/hardware_concurrency
   2 http://en.cppreference.com/w/cpp/thread/thread/detach
   2 http://en.cppreference.com/w/cpp/string/multibyte/mbsrtowcs
   2 http://en.cppreference.com/w/cpp/string/basic_string/hash
   2 http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
   2 http://en.cppreference.com/w/cpp/numeric/random/seed_seq/seed_seq
   2 http://en.cppreference.com/w/cpp/numeric/random/rand
   2 http://en.cppreference.com/w/cpp/numeric/math/nearbyint
   2 http://en.cppreference.com/w/cpp/numeric/complex/proj
   2 http://en.cppreference.com/w/cpp/memory/unique_ptr/reset
   2 http://en.cppreference.com/w/cpp/memory/shared_ptr/use_count
   2 http://en.cppreference.com/w/cpp/memory/new/operator_new
   2 http://en.cppreference.com/w/cpp/memory/enable_shared_from_this
   2 http://en.cppreference.com/w/cpp/language/sizeof...
   2 http://en.cppreference.com/w/cpp/language/namespace_alias
   2 http://en.cppreference.com/w/cpp/language/inline
   2 http://en.cppreference.com/w/cpp/language/destructor
   2 http://en.cppreference.com/w/cpp/iterator/rbegin
   2 http://en.cppreference.com/w/cpp/iterator/advance
   2 http://en.cppreference.com/w/cpp/io/manip/setw
   2 http://en.cppreference.com/w/cpp/io/manip/put_time
   2 http://en.cppreference.com/w/cpp/io/basic_ifstream/basic_ifstream
   2 http://en.cppreference.com/w/cpp/container/map/operator_at
   2 http://en.cppreference.com/w/cpp/container/list/list
   2 http://en.cppreference.com/w/cpp/atomic/atomic_thread_fence
   2 http://en.cppreference.com/w/cpp/algorithm/upper_bound
   2 http://en.cppreference.com/w/cpp/algorithm/set_intersection
   2 http://en.cppreference.com/w/cpp/algorithm/remove
   2 http://en.cppreference.com/w/cpp/algorithm/random_shuffle
   2 http://en.cppreference.com/w/cpp/algorithm/for_each
   2 http://en.cppreference.com/w/cpp/algorithm/adjacent_find
   2 http://en.cppreference.com/w/c/string/byte/strtok
   2 http://en.cppreference.com/w/c/string/byte/strspn
   2 http://en.cppreference.com/w/c/chrono/difftime
   1 http://en.cppreference.com/w/cpp/utility/variadic
   1 http://en.cppreference.com/w/cpp/thread/future/wait_for
   1 http://en.cppreference.com/w/cpp/string/byte/strcpy
   1 http://en.cppreference.com/w/cpp/string/byte/memcpy
   1 http://en.cppreference.com/w/cpp/string/basic_string/substr
   1 http://en.cppreference.com/w/cpp/string/basic_string/find_first_of
   1 http://en.cppreference.com/w/cpp/preprocessor/conditional
   1 http://en.cppreference.com/w/cpp/numeric/random/discrete_distribution/probabilities
   1 http://en.cppreference.com/w/cpp/numeric/math/log
   1 http://en.cppreference.com/w/cpp/numeric/math/floor
   1 http://en.cppreference.com/w/cpp/memory/c/malloc
   1 http://en.cppreference.com/w/cpp/locale/isalpha
   1 http://en.cppreference.com/w/cpp/language/using_declaration
   1 http://en.cppreference.com/w/cpp/language/template_specialization
   1 http://en.cppreference.com/w/cpp/language/dynamic_cast
   1 http://en.cppreference.com/w/cpp/io/ios_base/iword
   1 http://en.cppreference.com/w/cpp/container/queue/queue
   1 http://en.cppreference.com/w/cpp/container/forward_list/reverse
   1 http://en.cppreference.com/w/cpp/atomic/atomic_flag
   1 http://en.cppreference.com/w/cpp/algorithm/next_permutation
   1 http://en.cppreference.com/w/cpp/algorithm/max
   1 http://en.cppreference.com/w/c/chrono/strftime
   1 http://en.cppreference.com/w/Main_Page