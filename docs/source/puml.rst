Graph Pipeline Flow: SPIR-V™, Descriptors, Execution
====================================================

The following diagram shows how, starting with a compiled SPIR-V™ object and information about any constant tensors, a graph pipeline can be initialized.

.. plantuml:: puml/graph_pipeline.sequence.puml

Here the process of creating and binding descriptor sets with the graph pipeline is shown:

.. plantuml:: puml/graph_command.sequence.puml

This diagram shows how to setup the pipeline layout and graph pipeline objects, and then how to submit this workload to run.

.. plantuml:: puml/graph_layer.sequence.puml

Here the focus is more on how command buffers and descriptor sets are used:

.. plantuml:: puml/graph_command.class.puml

Finally a bit more detail on how a Data Graph pipeline can be set up:

.. plantuml:: puml/graph_pipeline.class.puml
