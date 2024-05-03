#include <iostream>

static void close_tag(std::string *temp, std::string *result) {
  if (temp[0] == "") {
    temp[0] = "<p>";
    temp[2] = "</p>";
  }

  result->append(temp[0] + temp[1] + temp[2] + "\n");

  temp[0] = "";
  temp[1] = "";
  temp[2] = "";
}

static std::string parse_raw_string(const std::string &content) {
  std::string result;
  std::string temp[3] = {"", "", ""};
  // @Incomplete(jejikeh): maybe i can use std::format here, to just replace the
  // 3 arrays. Then i could handle 'children' situations, maybe?

  for (std::int32_t i = 0; i < content.size(); i++) {
    if (content[i] == '#') {
      std::int32_t heading_level = 0;
      while (content[i] == '#' && i < content.size()) {
        i++;
        heading_level++;
      }

      temp[0] = "<h" + std::to_string(heading_level) + ">";
      temp[2] = "</h" + std::to_string(heading_level) + ">";
    }

    if (content[i] == '*') {
      if (i + 1 < content.size() && content[i + 1] != ' ') {
        temp[1] += "<em>";
        i++;

        while (i < content.size() && content[i] != '*') {
          temp[1] += content[i];
          i++;
        }

        temp[1] += "</em>";
        i++;
      }
    }

    if (content[i] == '\n') {
      close_tag(temp, &result);
      continue;
    }

    temp[1] += content[i];
  }

  close_tag(temp, &result);

  return result;
}

int main() {
  const std::string result = parse_raw_string("\n*huh*?");

  std::cout << result << std::endl;

  return EXIT_SUCCESS;
}