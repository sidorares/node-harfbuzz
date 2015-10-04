{
  "targets": [
    {
      "target_name": "addon",
      "sources": [
        "src/harfbuzz.cc",
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")", "/usr/local/include/freetype2", "/usr/local/include/harfbuzz"],
      "libraries": [ "-lfreetype", "-lharfbuzz" ]
    }
  ]
}
