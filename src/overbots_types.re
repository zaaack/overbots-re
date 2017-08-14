/* reason update: [@@bs.deriving {accessors: accessors}] */
type msg =
  | NothingYet
[@@bs.deriving {accessors: accessors}];

type game_msg =
  | TimeMsg (Tea.Time.t, string);

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
  | NoIntFlagsYet;

module IntFlagMap =
  Map.Make {
    type t = int_flag;
    let compare = compare;
  };

type int_flags = IntFlagMap.t int;

let init_int_flags () => IntFlagMap.(empty |> add NoIntFlagsYet 0);

type model = {
  msgs: list game_msg,
  resource_values: ResourceMap.t resource_value,
  bool_flags,
  int_flags
};
