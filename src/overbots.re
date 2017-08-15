[%bs.raw {|require('./overbots.scss')|}];

open Tea;

open Overbots_types;

let init () => {
  let model = {
    start_realtime: (-1.),
    current_realtime: (-1.),
    gametime: 0.,
    msgs: [],
    resource_values: Overbots_resources.init_resources_values (),
    bool_flags: init_bool_flags (),
    int_flags: init_int_flags (),
    float_flags: init_float_flags ()
  };
  (model, Cmd.none)
};

let update model msg =>
  switch msg {
  | UpdateFrame timeinfo =>
    let time = timeinfo.time *. 0.001;
    let model =
      if (model.start_realtime >= 0.0) {
        model
      } else {
        {...model, start_realtime: time, current_realtime: time, gametime: 0.0}
      };
    Overbots_update.update_state model time
  | ActionButtonClicked bid => Overbots_buttons.perform_button model bid
  };

let subscriptions _model => Sub.batch [AnimationFrame.every updateFrame];

let main = App.standardProgram {init, update, view: Overbots_view.view, subscriptions};

let overbotsRoot = [%bs.raw {|document.getElementById('overbots')|}];

main overbotsRoot ();
