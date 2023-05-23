#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <memory>
#include <bitset>
#include <functional>

using namespace std;

struct Node
{
  char ch;
  int freq;
  int id;
  shared_ptr<Node> left, right;
};

struct Compare
{
  bool operator()(const shared_ptr<Node> &a, const shared_ptr<Node> &b) const
  {
    if (a->freq == b->freq)
    {
      if (a->ch == '\0' && b->ch == '\0')
      {
        return a->id > b->id;
      }
      else if (a->ch == '\0' && b->ch != '\0')
      {
        return true;
      }
      else if (a->ch != '\0' && b->ch == '\0')
      {
        return false;
      }
      else
      {
        return a->ch > b->ch;
      }
    }
    return a->freq > b->freq;
  }
};

unordered_map<char, string> generateHuffmanCodes(const string &input)
{
  // Create frequency table
  unordered_map<char, int> freqTable;
  for (char c : input)
  {
    freqTable[c]++;
  }
  // Create priority queue of nodes
  priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Compare> pq;
  int id = 0;
  for (auto &pair : freqTable)
  {
    pq.push(make_shared<Node>(Node{pair.first, pair.second, id++, nullptr, nullptr}));
  }
  // Create huffman tree
  while (pq.size() > 1)
  {
    auto left = pq.top();
    pq.pop();
    auto right = pq.top();
    pq.pop();
    int totalFreq = left->freq + right->freq;
    pq.push(make_shared<Node>(Node{'\0', totalFreq, id++, left, right}));
  }
  // Traverse tree to generate codes
  unordered_map<char, string> codes;
  function<void(shared_ptr<Node>, string)> traverse = [&](shared_ptr<Node> node, string code)
  {
    if (!node)
    {
      return;
    }
    if (node->ch != '\0')
    {
      codes[node->ch] = code;
    }
    traverse(node->left, code + '0');
    traverse(node->right, code + '1');
  };
  if (!pq.empty())
  {
    traverse(pq.top(), "");
  }
  return codes;
}

//Helper function to format encoded string
string encodeString(const string &input, const unordered_map<char, string> &codes)
{
  string encoded;
  for (char c : input)
  {
    encoded += codes.at(c) + " ";
  }
  return encoded;
}

//Function to decode encoded string
string decodeHuffmanCodes(const string &input, const unordered_map<string, char> &codes)
{
  string decoded;
  int i = 0;
  while (i < input.size())
  {
    string code;
    while (i < input.size() && input[i] != ' ')
    {
      code += input[i];
      i++;
    }
    if (codes.find(code) != codes.end())
    {
      decoded += codes.at(code);
    }
    else
    {
      decoded += code;
    }
    i++;
  }
  return decoded;
}

int main()
{
  while (true)
  {
    string input;
    cout << "Enter 'exit' to quit the program\n\n";
    cout << "Enter input string: ";
    getline(cin, input);

    if (input == "exit")
    {
      break;
    }

    auto codes = generateHuffmanCodes(input);
    auto encoded = encodeString(input, codes);

    cout << "Encoded string: " << encoded << endl;

    auto reverseCodes = unordered_map<string, char>();
    for (const auto &p : codes)
    {
      reverseCodes[p.second] = p.first;
    }

    auto decoded = decodeHuffmanCodes(encoded, reverseCodes);

    cout << "Decoded string: " << decoded << endl;

    cout << "Enter encoded string: ";
    getline(cin, input);

    decoded = decodeHuffmanCodes(input, reverseCodes);
    cout << "Decoded string: " << decoded << endl;
  }

  return 0;
}
