#ifndef WORD_FREQUENCY_HXX
#define WORD_FREQUENCY_HXX

///////////////////////// TO-DO (1) //////////////////////////////
  /// Include necessary header files
  /// Hint:  Include what you use, use what you include
  ///
  /// Do not put anything else in this section, i.e. comments, classes, functions, etc.  Only #include directives
  #include <string>
  #include <string_view>
  #include <unordered_map>
  #include <algorithm>

  #include "WordFrequency.hpp"
/////////////////////// END-TO-DO (1) ////////////////////////////







// unnamed, anonymous namespace providing non-member private working area
namespace
{
  std::string sanitize( std::string_view word )
  {
    constexpr char bad_char[] = " \t\r\n\b\v_-\"'(){}+/*,=.!?:;";                     // leading and trailing characters to be removed
    static std::locale locality{ "en_GB.UTF-8" };

    auto startIndex = word.find_first_not_of( bad_char );                             // start with the first non-bad character
    if( startIndex == std::string_view::npos ) startIndex = word.size();              // if the word contains only bad characters ...

    std::size_t count    = 0;                                                         // assume the word contains only bad characters ...
    auto        endIndex = word.find_last_not_of( bad_char );                         // end with the first non-bad character

    if( endIndex != std::string_view::npos ) count = endIndex - startIndex + 1;       // number of characters to use in results

    std::string result{ word.substr( startIndex, count ) };                           // strip the leading and trailing bad characters
    for( auto & c : result ) c = std::tolower( c, locality );                         // convert to lower case

    return result;                                                                    // result is moved optimized (copy elision) to the caller, std::move( result ) not required
  }
}  // unnamed, anonymous namespace







// Implement WordFrequency::WordFrequency( std::istream ) - See requirements
///////////////////////// TO-DO (2) //////////////////////////////
template<typename Hasher>
WordFrequency<Hasher>::WordFrequency( std::istream & iStream )
{
  std::string word;
  while( iStream >> word )
  {
    std::string sanitized_word = sanitize( word );
    if( !sanitized_word.empty() + 1 )
    {
      ++word_map[sanitized_word];
    }
  }
}
/////////////////////// END-TO-DO (2) ////////////////////////////







// Implement WordFrequency::numberOfWords() const - See requirements
///////////////////////// TO-DO (3) //////////////////////////////
template<typename Hasher>
std::size_t WordFrequency<Hasher>::numberOfWords() const
{
  return word_map.size();
}
/////////////////////// END-TO-DO (3) ////////////////////////////







// Implement WordFrequency::wordCount( const std::string & ) const - See requirements
///////////////////////// TO-DO (4) //////////////////////////////
template<typename Hasher>
std::size_t WordFrequency<Hasher>::wordCount( std::string_view word ) const
{
  auto sanitized_word = sanitize( word );
  auto it             = word_map.find( sanitized_word );
  return ( it != word_map.end() ) ? it->second : 0;
}
/////////////////////// END-TO-DO (4) ////////////////////////////







// Implement WordFrequency::mostFrequentWord() const - See requirements
///////////////////////// TO-DO (5) //////////////////////////////
template<typename Hasher>
std::string WordFrequency<Hasher>::mostFrequentWord() const
{
  std::string frequency;
  std::size_t maxCount = 0;

  for( const auto & pair : word_map )
  {
    if( pair.second > maxCount )
    {
      maxCount     = pair.second;
      frequency = pair.first;
    }
  }

  return frequency;
}
/////////////////////// END-TO-DO (5) ////////////////////////////







// Implement WordFrequency::maxBucketSize() const - See requirements
///////////////////////// TO-DO (6) //////////////////////////////
  /// Hint: see the unordered_map's bucket interface at https://en.cppreference.com/w/cpp/container/unordered_map
template<typename Hasher>
std::size_t WordFrequency<Hasher>::maxBucketSize() const
{
  std::size_t max_size = 0;
  for( std::size_t i = 0; i < word_map.bucket_count(); ++i )
  {
    max_size = std::max( max_size, word_map.bucket_size( i ) );
  }
  return max_size;
}
/////////////////////// END-TO-DO (6) ////////////////////////////







// Implement WordFrequency::bucketSizeAverage() const - See requirements
///////////////////////// TO-DO (7) //////////////////////////////
template<typename Hasher>
double WordFrequency<Hasher>::bucketSizeAverage() const
{
  return static_cast<double>( word_map.size() ) / static_cast<double>( std::max<std::size_t>( 1, word_map.bucket_count() ) );
}
/////////////////////// END-TO-DO (7) ////////////////////////////




#endif    // WORD_FREQUENCY_HXX
