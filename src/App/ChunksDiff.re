open Compare.Chunks;

module ChunksDiff =
  GenericDiff.Make({
    type a = chunk;

    let componentName = "ChunksDiff";
  });

let make = ChunksDiff.make;
type props = ChunksDiff.props;