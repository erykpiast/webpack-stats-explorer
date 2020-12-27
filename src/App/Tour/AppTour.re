[@react.component]
let make =
    (
      ~state: UrlState.t,
      ~onState: UrlState.t => unit,
      ~isOpen: bool,
      ~onClose: unit => unit,
    ) => {
  let steps =
    React.useMemo1(
      () => {
        let setState =
            (
              i,
              ~navigationPath=state.navigationPath,
              ~index=state.index,
              ~tab=state.tab,
              ~sourceTree=state.sourceTree,
              ~splitView=state.splitView,
              ~timeline=state.timeline,
              ~urls=state.urls,
              (),
            ) => {
          let urlState =
            UrlState.{
              navigationPath,
              index,
              tab,
              sourceTree,
              splitView,
              timeline,
              urls,
            };
          onState(urlState);
        };

        [
          AppTour__Step1.getStep,
          AppTour__Step2.getStep,
          AppTour__Step3.getStep,
          AppTour__Step4.getStep,
          AppTour__Step5.getStep,
          AppTour__Step6.getStep,
          AppTour__Step7.getStep,
          AppTour__Step8.getStep,
          AppTour__Step9.getStep,
          AppTour__Step10.getStep,
          AppTour__Step11.getStep,
          AppTour__Step12.getStep,
          AppTour__Step13.getStep,
          AppTour__Step14.getStep,
          AppTour__Step15.getStep,
          AppTour__Step16.getStep,
          AppTour__Step17.getStep,
          AppTour__Step18.getStep,
          AppTour__Step19.getStep,
          AppTour__Step20.getStep,
          AppTour__Step21.getStep,
          AppTour__Step22.getStep,
          AppTour__Step23.getStep,
          AppTour__Step24.getStep,
          AppTour__Step25.getStep,
          AppTour__Step26.getStep,
          AppTour__Step27.getStep,
          AppTour__Step28.getStep,
          AppTour__Step29.getStep,
          AppTour__Step30.getStep,
          AppTour__Step31.getStep,
          AppTour__Step32.getStep,
          AppTour__Step33.getStep,
          AppTour__Step34.getStep,
          AppTour__Step35.getStep,
        ]
        |> List.mapi((i, getStep) => getStep(setState(i)));
      },
      [|onState|],
    );

  <Reactour isOpen steps onRequestClose=onClose />;
};
