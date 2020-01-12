module BraceStyle = {
  type t = [
    | `collapse
    | `expand
    | `endExpand
    | `none
    | `preserveInline
    | `collapsePreserveInline
  ];

  let toString = fun
    | `collapse => "collapse"
    | `expand => "expand"
    | `endExpand => "end-expand"
    | `none => "none"
    | `preserveInline => "preserve-inline"
    | `collapsePreserveInline => "collapse,preserve-inline"
  ;
}

module Templating = {
  type t = [
    | `auto
    | `none
    | `django
    | `erb
    | `handlebars
    | `php
  ];

  let toString = fun
    | `auto => "auto"
    | `none => "none"
    | `django => "django"
    | `erb => "erb"
    | `handlebars => "handlebars"
    | `php => "php"
  ;
}

module OperatorPosition = {
  type t = [
    | `beforeNewline
    | `afterNewline
    | `preserveNewline
  ];

  let toString = fun
    | `beforeNewline => "before-newline"
    | `afterNewline => "after-newline"
    | `preserveNewline => "preserve-newline"
  ;
}

[@bs.deriving abstract]
type options = {
  indent_size: option(int),
  indent_char: option(string),
  indent_with_tabs: option(bool),
  editorconfig: option(bool),
  eol: option(string),
  end_with_newline: option(bool),
  indent_level: option(int),
  preserve_newlines: option(bool),
  max_preserve_newlines: option(int),
  space_in_paren: option(bool),
  space_in_empty_paren: option(bool),
  jslint_happy: option(bool),
  space_after_anon_function: option(bool),
  space_after_named_function: option(bool),
  brace_style: option(BraceStyle.t),
  unindent_chained_methods: option(bool),
  break_chained_methods: option(bool),
  keep_array_indentation: option(bool),
  unescape_strings: option(bool),
  wrap_line_length: option(int),
  e4x: option(bool),
  comma_first: option(bool),
  operator_position: option(OperatorPosition.t),
  indent_empty_lines: option(bool),
  templating: option(list(Templating.t))
};

[@bs.module "js-beautify"] external jsBeautify: string => options => string = "js";

let beautify = (
  ~indent_size=?,
  ~indent_char=?,
  ~indent_with_tabs=?,
  ~editorconfig=?,
  ~eol=?,
  ~end_with_newline=?,
  ~indent_level=?,
  ~preserve_newlines=?,
  ~max_preserve_newlines=?,
  ~space_in_paren=?,
  ~space_in_empty_paren=?,
  ~jslint_happy=?,
  ~space_after_anon_function=?,
  ~space_after_named_function=?,
  ~brace_style=?,
  ~unindent_chained_methods=?,
  ~break_chained_methods=?,
  ~keep_array_indentation=?,
  ~unescape_strings=?,
  ~wrap_line_length=?,
  ~e4x=?,
  ~comma_first=?,
  ~operator_position=?,
  ~indent_empty_lines=?,
  ~templating=?,
  code
) => jsBeautify(code, options(
  ~indent_size?,
  ~indent_char?,
  ~indent_with_tabs?,
  ~editorconfig?,
  ~eol?,
  ~end_with_newline?,
  ~indent_level?,
  ~preserve_newlines?,
  ~max_preserve_newlines?,
  ~space_in_paren?,
  ~space_in_empty_paren?,
  ~jslint_happy?,
  ~space_after_anon_function?,
  ~space_after_named_function?,
  ~brace_style?,
  ~unindent_chained_methods?,
  ~break_chained_methods?,
  ~keep_array_indentation?,
  ~unescape_strings?,
  ~wrap_line_length?,
  ~e4x?,
  ~comma_first?,
  ~operator_position?,
  ~indent_empty_lines?,
  ~templating?,
));
