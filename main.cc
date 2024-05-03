#include <iostream>

#define OPEN_TAG 0
#define CONTENT 1
#define CLOSE_TAG 2

static void close_tag(std::string *current_tag, std::string *result) {
  if (current_tag[OPEN_TAG] == "") {
    current_tag[OPEN_TAG] = "<p>";
    current_tag[CLOSE_TAG] = "</p>";
  }

  result->append(current_tag[OPEN_TAG] + current_tag[CONTENT] +
                 current_tag[CLOSE_TAG] + "\n");

  current_tag[OPEN_TAG] = "";
  current_tag[CONTENT] = "";
  current_tag[CLOSE_TAG] = "";
}

static std::string parse_raw_string(const std::string &content) {
  std::string result;
  std::string current_tag[3] = {"", "", ""};
  // @Incomplete(jejikeh): maybe i can use std::format here, to just replace the
  // 3 arrays. Then i could handle 'children' situations, maybe?

  for (std::int32_t i = 0; i < content.size(); i++) {
    if (content[i] == '#') {
      std::int32_t heading_level = 0;
      while (content[i] == '#' && i < content.size()) {
        i++;
        heading_level++;
      }

      current_tag[OPEN_TAG] = "<h" + std::to_string(heading_level) + ">";
      current_tag[CLOSE_TAG] = "</h" + std::to_string(heading_level) + ">";
    }

    if (content[i] == '*') {
      if (i + 1 < content.size() && content[i + 1] != ' ') {
        current_tag[CONTENT] += "<em>";
        i++;

        while (i < content.size() && content[i] != '*') {
          current_tag[CONTENT] += content[i];
          i++;
        }

        current_tag[CONTENT] += "</em>";
        i++;
      }
    }

    if (content[i] == '\n') {
      close_tag(current_tag, &result);
      continue;
    }

    current_tag[CONTENT] += content[i];
  }

  close_tag(current_tag, &result);

  return result;
}

int main() {
  const std::string result = parse_raw_string("\n*huh*?");

  std::cout << result << std::endl;

  return EXIT_SUCCESS;
}