type game_msg =
  | TimeMsg (Tea.Time.t, string);

type button_id =
  | UnfoldSolarPanels
  | DeployDrill;

/* reason update: [@@bs.deriving {accessors: accessors}] */
type msg =
  | UpdateFrame Tea.AnimationFrame.t
  | ActionButtonClicked button_id
[@@bs.deriving {accessors: accessors}];

type resource_flag =
  | Energy
  | IronOxide
  | RawSilicon;

module ResourceMap =
  Map.Make {
    type t = resource_flag;
    let compare = compare;
  };

type resource_value = float;

type bool_flag =
  | InternalPowerEnabled
  | SolarPanelsReadyToUnfold
  | SolarPanelsGenerating
  | DrillDeployed;

module BoolFlagSet =
  Set.Make {
    type t = bool_flag;
    let compare = compare;
  };

type bool_flags = BoolFlagSet.t;

let init_bool_flags () => BoolFlagSet.empty;

type int_flag =
  | TimeActionIdx;

module IntFlagMap =
  Map.Make {
    type t = int_flag;
    let compare = compare;
  };

type int_flags = IntFlagMap.t int;

let init_int_flags () => IntFlagMap.(empty |> add TimeActionIdx 0);

type float_flag =
  | BasicSolarPanelSelfGeneration;

module FloatFlagMap =
  Map.Make {
    type t = float_flag;
    let compare = compare;
  };

type float_flags = FloatFlagMap.t float;

let init_float_flags () => FloatFlagMap.(empty |> add BasicSolarPanelSelfGeneration 0.0);

type model = {
  start_realtime: Tea.Time.t,
  current_realtime: Tea.Time.t,
  gametime: Tea.Time.t,
  msgs: list game_msg,
  resource_values: ResourceMap.t resource_value,
  bool_flags,
  int_flags,
  float_flags
};
