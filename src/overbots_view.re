open Tea.Html;

open Overbots_types;

let view_container enabled id title children =>
  if (not enabled) {
    noNode
  } else {
    div
      [class' ("container container-" ^ id)]
      [
        div [class' "title"] [text title],
        div [class' ("scroller " ^ id)] children
      ]
  };

let format_value value =>
  if (value < 10000.0) {
    let str = string_of_float value;
    let str = String.sub str 0 (min (String.length str) 6);
    str ^ String.make (6 - String.length str) '0'
  } else {
    string_of_int (int_of_float value)
  };

let view_resources_category_resource model (rid, name, id) => {
  let r = Overbots_resources.get_resource_module rid;
  module R = (val r);
  if (not (R.shown model)) {
    []
  } else {
    let value = format_value (Overbots_resources.get_resource_value rid model);
    [
      div
        [class' ("resources resource-" ^ id)]
        [
          div [class' "resource-name"] [text name],
          div [class' "resource-value"] [text value]
        ]
    ]
  }
};

let view_resources_categories model (name, id, resources) => {
  let children =
    List.map (view_resources_category_resource model) resources |> List.flatten;
  if (children === []) {
    []
  } else {
    let children =
      if (name == "") {
        children
      } else {
        [div [class' "category-title"] [text name], ...children]
      };
    [div [class' ("resource-category resource-category-" ^ id)] children]
  }
};

let view_resources model =>
  List.map
    (view_resources_categories model) Overbots_resources.displayed_resources |> List.flatten;

let view_buttons model => [];

let view_scanner model => [];

let view_msgs model => [];

let view model =>
  div
    [class' "overbots"]
    [
      div [class' "header"] [text "Overbots"],
      div
        [class' "body"]
        [
          view_container true "resources" " Resources" (view_buttons model),
          view_container true "actions" " Actions" (view_buttons model),
          view_container true "scanner" " Scanner" (view_buttons model)
        ],
      view_container true "msgs" "Messages" (view_msgs model)
    ];
