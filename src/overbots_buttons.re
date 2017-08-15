open Overbots_types;

open Overbots_actions;

open Overbots_flags;

open Overbots_resources;

let displayed_buttons = [
  (
    "Perform",
    "perform",
    [
      (UnfoldSolarPanels, "unfold-solar-panels", "Unfold Solar Panels"),
      (DeployDrill, "deploy-drill", "Deploy Drill")
    ]
  )
];

let button_cost _model bid =>
  switch bid {
  | UnfoldSolarPanels => [(Energy, 100.)]
  | DeployDrill => [(Energy, 50.)]
  };

let button_enabled model bid =>
  switch bid {
  | UnfoldSolarPanels =>
    not (bool_flag_exists SolarPanelsGenerating model) &&
    bool_flag_exists SolarPanelsReadyToUnfold model
  | DeployDrill =>
    not (bool_flag_exists DrillDeployed model) && bool_flag_exists SolarPanelsGenerating model
  };

let button_temporarily_disabled model bid =>
  switch bid {
  | DeployDrill => cost_resources (button_cost model DeployDrill) model === None
  | _button => false
  };

let button_actions _model bid =>
  switch bid {
  | UnfoldSolarPanels => [
      ActionSetBoolFlag SolarPanelsGenerating,
      ActionClearBoolFlag SolarPanelsReadyToUnfold,
      ActionAddMsg "Energy is now being generated, now to acquire simple minerals by drilling"
    ]
  | DeployDrill => [
      ActionSetBoolFlag DrillDeployed,
      ActionAddMsg "Now that I've started acquiring resources I need to active my internal refineries to prepare the resources for use"
    ]
  };

let perform_button orig_model id =>
  Tea.(
    if (not (button_enabled orig_model id) || button_temporarily_disabled orig_model id) {
      (orig_model, Cmd.none)
    } else {
      switch (cost_resources (button_cost orig_model id) orig_model) {
      | None => (orig_model, Cmd.none)
      | Some model =>
        let model = perform_actions model (button_actions model id);
        switch id {
        | _ => (model, Cmd.none)
        }
      }
    }
  );
