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
    [
      (IronOxide, "Iron Oxide", "ironoxide"),
      (RawSilicon, "Raw Silicon", "rawsilicon")
    ]
  )
];

let get_resource_module rid => ResourceMap.find rid all_resources;

let get_resource_value rid model => ResourceMap.find rid model.resource_values;

type resource_value_state =
  | ValueTooLow
  | ValueTooHigh (model, resource_value)
  | ValueSuccess model;

let set_resource_value rid value model => {
  module R = (val get_resource_module rid);
  let (rmin, rmax) = R.get_value_range model;
  if (value < rmin) {
    ValueTooLow
  } else if (value > rmax) {
    let resource_values = ResourceMap.add rid rmax model.resource_values;
    /*
       extends model with some member
       in OCaml: `{model with resource_values}`
     */
    ValueTooHigh ({...model, resource_values}, value -. rmax)
  } else {
    let resource_values = ResourceMap.add rid value model.resource_values;
    ValueSuccess {...model, resource_values}
  }
};

let add_resource_value rid delta model => {
  let value = delta +. get_resource_value rid model;
  set_resource_value rid value model
};

let init_resources_values () => {
  let resource_folder rid _r acc => ResourceMap.add rid 0.0 acc;
  ResourceMap.fold resource_folder all_resources ResourceMap.empty
};
