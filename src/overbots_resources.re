open Overbots_types;

module type Resource = {
  let id: resource_flag;
  let shown: model => bool;
  let get_value_range: model => (resource_value, resource_value);
};

module Energy: Resource = {
  let id = Energy;
  let shown _model => true;
  let get_value_range _model => (0.0, 100.0);
};

module IronOxide: Resource = {
  let id = IronOxide;
  let shown _model => true;
  let get_value_range _model => (0.0, 100.0);
};

module RawSilicon: Resource = {
  let id = RawSilicon;
  let shown _model => true;
  let get_value_range _model => (0.0, 100.0);
};

let all_resources =
  ResourceMap.(
    empty |> add Energy ((module Energy): (module Resource)) |>
    add IronOxide ((module IronOxide): (module Resource)) |>
    add RawSilicon ((module RawSilicon): (module Resource))
  );

let displayed_resources = [
  ("", "global", [(Energy, "Energy", "energy")]),
  (
    "Raw",
    "raw",
    [(IronOxide, "Iron Oxide", "ironoxide"), (RawSilicon, "Raw Silicon", "rawsilicon")]
  )
];

let get_resource_module rid => ResourceMap.find rid all_resources;

let get_resource_value rid model => ResourceMap.find rid model.resource_values;

type resource_value_state =
  | ValueTooLow
  | ValueTooHigh (model, resource_value)
  | ValueSuccess model;
