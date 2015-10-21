#include "main.h"


//algo parser url => extraire info => placer dans la queue => loop

template<typename T>
bool checkElementIsInVector(const T& elem, const std::vector<T>& container)
{
	if ( std::find(container.begin(), container.end(), elem) != container.end() )
		return true;
	else
		return false;
}

bool is_there(std::string haystack, std::vector<std::string> needles) {

  for(auto needle : needles ){
    auto pos = haystack.find(needle);
    if(pos != std::string::npos){
      //return pos;
		return true;
    }
  } 
  return false;
  //return std::string::npos;
}  

void parseData(std::string &content, WebPage &page, queue<WebPage> &queue, std::vector<WebPage> visited){

	std::smatch m;
	const std::regex rmv_all("[\\r|\\n]");
	std::string s2 = std::regex_replace(content, rmv_all, "");
	content = s2;

	const std::regex e("<a\\s+href\\s*=\\s*(\"([^\"]*)\")|('([^']*)')\\s*>");
	
    while (std::regex_search (content,m,e)) 
	{
		vector<string> search;
		search.push_back(".pdf");
		search.push_back(".css");
		search.push_back(".rss");
		if( !is_there( m[2].str(), search) )
		{
			search.clear();
			search.push_back("http://");
			search.push_back("https://");
			if( !is_there( m[2].str(), search) ) // C'est un lien local => /page
			{ 
				WebPage p(page.getHosname(),  m[2].str());
				if( !checkElementIsInVector<WebPage>(p,visited) ) { //existe pas
					queue.push(p);
					visited.push_back(p);
				}
			}
			else  //C'est une url hostname
			{
				WebPage p(m[2].str());
				if( !checkElementIsInVector(p,visited) ) { //existe pas
					queue.push(p);
					visited.push_back(p);
				}
			}
		}
		content = m.suffix().str();
	}

	const std::regex email("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$");
	m = std::smatch();
	while (std::regex_search (s2,m,email)) {
		for (auto x:m) 
		std::cout << x << std::endl << " ";
		cout << m[2] << endl;
		s2 = m.suffix().str();
	 }

}

void main(){

	HttpGet httpreq;
	queue<WebPage> myq;
	vector<WebPage> visited;

	WebPage startPage("http://people.ac.upc.edu/", "nrajovic/");
	myq.push(startPage);
	//myset.insert(startPage);
	while (!myq.empty())
	  {
		  WebPage next = myq.front();
		  myq.pop();
		  cout << "Current link : " << next.getfullPath() << endl;
		  std::string content = httpreq.get(next.getfullPath());
		  parseData(content, next, myq, visited);
	  }
	
  std::cout << '\n';
  
  system("PAUSE");

}